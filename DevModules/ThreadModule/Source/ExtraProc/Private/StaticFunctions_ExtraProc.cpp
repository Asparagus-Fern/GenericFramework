// Copyright ChenTaiye 2025. All Rights Reserved.

#include "StaticFunctions_ExtraProc.h"

#include "ExtraProcThread.h"
#include "StaticFunctions_Thread.h"
#include "ThreadManager.h"
#include "Type/DebugType.h"
#include "Manager/ManagerStatics.h"

bool FStaticFunctions_ExtraProc::LaunchExtraProc(const FProcStartUpInfo& Info, FGuid& ProcId)
{
	if (Info.ProcFile.FilePath.IsEmpty())
	{
		GenericLOG(GenericLogExtraProc, Error, TEXT("Launch Proc Fial! Invalid File Name"))
		return false;
	}

	const FString Url = FPaths::Combine(FPaths::ProjectDir(), Info.ProcFile.FilePath);

	if (!ensureAlways(FPaths::IsUnderDirectory(Url, FPaths::Combine(FPaths::ProjectDir(), TEXT("Extras")))))
	{
		GenericLOG(GenericLogExtraProc, Warning, TEXT("Proc Is Not Under The Path : /Project/Extras"))
		return false;
	}

	if (!ensure(FPaths::FileExists(Url)))
	{
		GenericLOG(GenericLogExtraProc, Warning, TEXT("Invalid File : %s"), *Url)
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

bool FStaticFunctions_ExtraProc::LaunchExtraProc(const FString& Urls, const FString& Params, bool RunInBackground, bool CreatePipe, bool TerminateWithParentProc, FGuid& OutProcId)
{
	const TSharedPtr<FExtraProcThread> ExtraStartProcRunnable = NewGenericThread<FExtraProcThread>(Urls, Params, RunInBackground, TerminateWithParentProc, CreatePipe);

	check(!ExtraStartProcRunnable->GetIsRunning())

	if (!ExtraStartProcRunnable->Launch())
	{
		return false;
	}

	const FGuid ProcId = ExtraStartProcRunnable->GetThreadGuid();
	GenericLOG(GenericLogExtraProc, Log, TEXT("Launch Extra proc Success, [Thread Id %s] , %s"), *ProcId.ToString(), *ExtraStartProcRunnable->GetCommandline())

	OutProcId = ProcId;
	return true;
}

void FStaticFunctions_ExtraProc::TerminationExtraProc(FGuid ProcId, bool bKillTree)
{
	if (UThreadManager* ThreadManager = GetManagerOwner<UThreadManager>())
	{
		TSharedPtr<FExtraProcThread> ExtraProcThread = ThreadManager->GetThread<FExtraProcThread>(ProcId);
		if (ExtraProcThread.IsValid())
		{
			ExtraProcThread->SetKillTree(bKillTree);
			ExtraProcThread->Terminate();
		}
	}
}
