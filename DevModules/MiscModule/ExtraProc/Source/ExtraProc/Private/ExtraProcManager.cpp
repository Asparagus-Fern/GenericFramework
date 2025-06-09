// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ExtraProcManager.h"

#include "ExtraProcSettings.h"
#include "ExtraProcThread.h"
#include "BPFunctions/BPFunctions_File.h"
#include "Async/TaskGraphInterfaces.h"
#include "Async/Async.h"

#if PLATFORM_WINDOWS
#include "Platform/WindowsExtraProcHelper.h"
#endif

#if WITH_EDITOR
#include "Editor.h"
#endif

bool UExtraProcManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UExtraProcManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

#if WITH_EDITOR
	FEditorDelegates::BeginPIE.AddUObject(this, &UExtraProcManager::BeginPIE);
	FEditorDelegates::EndPIE.AddUObject(this, &UExtraProcManager::EndPIE);
#else
	LanchAllProc();
#endif

	if (!FPaths::DirectoryExists(ExtrasPath))
	{
		UBPFunctions_File::CreateDirectory(ExtrasPath);
	}
}

void UExtraProcManager::Deinitialize()
{
	Super::Deinitialize();

#if WITH_EDITOR
	FEditorDelegates::BeginPIE.RemoveAll(this);
	FEditorDelegates::EndPIE.RemoveAll(this);
#else
	KillAllProc();
#endif

	UnRegisterManager();
}

void UExtraProcManager::LanchAllProc()
{
	for (auto ProcInfo : UExtraProcSettings::Get()->AutoStartUpExtraProcList)
	{
		FExtraProcHandle ProcHandle;

		if (!ProcInfo.bAutoLaunch)
		{
			continue;
		}

		if (!LaunchExtraProc(ProcInfo.ExtraStartProcInfo, ProcHandle))
		{
			GenericLOG(GenericLogNetwork, Warning, TEXT("Auto launch extra start proc fail. Execute path : %s"), *ProcInfo.ExtraStartProcInfo.ProcFile.FilePath)
		}
	}
}

void UExtraProcManager::KillAllProc()
{
	TArray<uint16> AllProcId;
	ExtraProcHandle.GetKeys(AllProcId);

	for (const uint16 ProcId : AllProcId)
	{
		TerminationExtraProc(ProcId, true);
	}

	ExtraProcHandle.Empty();
}

#if WITH_EDITOR

void UExtraProcManager::BeginPIE(bool bIsSimulating)
{
	LanchAllProc();
}

void UExtraProcManager::EndPIE(bool bIsSimulating)
{
	KillAllProc();
}

#endif

bool UExtraProcManager::IsProcValid(const FExtraProcHandle& InHandle) const
{
	if (InHandle.IsValid())
	{
		const uint16 ProcId = InHandle.GetProcId();

		if (ExtraProcHandle.Contains(ProcId))
		{
			const auto ExtraProcThread = ExtraProcHandle[ProcId];
			return ExtraProcThread.IsValid();
		}
	}

	return false;
}

bool UExtraProcManager::IsProcRunning(const FExtraProcHandle& InHandle) const
{
	if (InHandle.IsValid())
	{
		const uint16 ProcId = InHandle.GetProcId();

		if (ExtraProcHandle.Contains(ProcId))
		{
			const auto ExtraProcThread = ExtraProcHandle[ProcId];
			return ExtraProcThread.IsValid() && ExtraProcThread->Update();
		}
	}

	return false;
}

FTimespan UExtraProcManager::GetDuration(const FExtraProcHandle& InHandle) const
{
	if (InHandle.IsValid())
	{
		const uint16 ProcId = InHandle.GetProcId();

		if (ExtraProcHandle.Contains(ProcId))
		{
			const auto ExtraProcThread = ExtraProcHandle[ProcId];
			return ExtraProcThread->GetDuration();
		}
	}

	return FTimespan::Zero();
}

bool UExtraProcManager::LaunchExtraProc(const FProcStartUpInfo& Info, FExtraProcHandle& ProcHandle)
{
	uint16 ProcID;
	if (LaunchExtraProc(Info, ProcID))
	{
		ProcHandle = FExtraProcHandle(ProcID);
		return true;
	}

	return false;
}


bool UExtraProcManager::LaunchExtraProc(const FProcStartUpInfo& Info, uint16& ProcId)
{
	if (Info.ProcFile.FilePath.IsEmpty())
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Launch Proc Fial! Invalid File Name"))
		return false;
	}
	
	const FString Url = FPaths::Combine(FPaths::ProjectDir(), Info.ProcFile.FilePath);
	
	if (!ensureAlways(FPaths::IsUnderDirectory(Url, FPaths::Combine(FPaths::ProjectDir(), TEXT("Extras")))))
	{
		GenericLOG(GenericLogNetwork, Warning, TEXT("Proc Is Not Under The Path : /Project/Extras"))
		return false;
	}
	
	if (!ensure(FPaths::FileExists(Url)))
	{
		GenericLOG(GenericLogNetwork, Warning, TEXT("Invalid File : %s"), *Url)
		return false;
	}
	
	FString CommandLine;
	auto AddParams = [&CommandLine](const FString& Key, const FString& Value)
	{
		// 建不能为空
		if (Key.IsEmpty())
		{
			return;
		}
	
		if (Value.IsEmpty())
		{
			CommandLine += FString::Printf(TEXT("-%s=%s"), *Key, *Value);
		}
		else
		{
			CommandLine += FString::Printf(TEXT(" -%s"), *Key);
		}
	};
	
	if (!Info.StartParams.IsEmpty())
	{
		for (const auto& Param : Info.StartParams)
		{
			AddParams(Param.Key, Param.Value);
		}
	}
	
	return LaunchExtraProc(Url, CommandLine, Info.bRunInBackground, Info.bCreatePipe, true, ProcId);
}


bool UExtraProcManager::LaunchExtraProc(const FString& Urls, const FString& Params, bool RunInBackground, bool CreatePipe, bool ShouldEndWithParentProcTermination, uint16& OutProcId)
{
	const TSharedPtr<FExtraProcThread> ExtraStartProcRunnable = MakeShareable(new FExtraProcThread(Urls, Params, RunInBackground, CreatePipe));
	ExtraStartProcRunnable->OnExtraProcCompleted().BindUObject(this, &UExtraProcManager::OnExtraProcCompleted);

	check(!ExtraStartProcRunnable->IsRunning())

	if (!ExtraStartProcRunnable->Launch())
	{
		return false;
	}

	if (ShouldEndWithParentProcTermination)
	{
#if PLATFORM_WINDOWS
		const FProcHandle Proc = ExtraStartProcRunnable->GetProcHandle();

		if (!FWindowsExtraProcHelper::SetProcEndWithCurrentProcTermination(Proc))
		{
			GenericLOG(GenericLogNetwork, Warning, TEXT("Prco Add Job Fail."))
		}
#endif
	}

	const uint16 ProcId = ExtraStartProcRunnable->GetProcId();
	GenericLOG(GenericLogNetwork, Log, TEXT("Lauch extra start proc Success, [Proc Id %d] , %s"), ProcId, *ExtraStartProcRunnable->GetCommandline())

	ExtraProcHandle.Emplace(ProcId, ExtraStartProcRunnable);
	OutProcId = ProcId;
	return true;
}

void UExtraProcManager::TerminationExtraProc(FExtraProcHandle& ProcHandle, bool bKillTree)
{
	if (!IsProcValid(ProcHandle)) 
	{
		return;
	}

	TerminationExtraProc(ProcHandle.GetProcId(), bKillTree);
	ProcHandle = FExtraProcHandle();
}

void UExtraProcManager::TerminationExtraProc(uint16 ProcId, bool bKillTree)
{
	if (ExtraProcHandle.Contains(ProcId))
	{
		const auto ExtraProcThread = ExtraProcHandle[ProcId];

		if (ExtraProcThread.IsValid())
		{
			ExtraProcThread->Cancle(bKillTree);
		}

		ExtraProcHandle.Remove(ProcId);
	}
}

void UExtraProcManager::OnExtraProcCompleted(int32 ReturnCode, uint16 ProcId)
{
	auto Execute = [ProcId, this]()
	{
		ExtraProcHandle.Remove(ProcId);
	};

	AsyncTask(ENamedThreads::GameThread, Execute);
}


