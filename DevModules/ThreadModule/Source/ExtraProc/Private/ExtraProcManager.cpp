// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ExtraProcManager.h"

#include "ExtraProcSettings.h"
#include "ExtraProcThread.h"
#include "StaticFunctions_ExtraProc.h"
#include "StaticFunctions_Thread.h"
#include "ThreadManager.h"
#include "BPFunctions/BPFunctions_File.h"
#include "Async/TaskGraphInterfaces.h"
#include "Async/Async.h"
#include "Manager/ManagerStatics.h"

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
#endif

	UnRegisterManager();
}

#if WITH_EDITOR

void UExtraProcManager::BeginPIE(bool bIsSimulating)
{
	LaunchAllProc();
}

#endif

void UExtraProcManager::LaunchAllProc()
{
	for (auto ProcInfo : UExtraProcSettings::Get()->AutoStartUpExtraProcList)
	{
		if (!ProcInfo.bAutoLaunch)
		{
			continue;
		}

		FGuid ProcGuid;
		if (!FStaticFunctions_ExtraProc::LaunchExtraProc(ProcInfo.ExtraStartProcInfo, ProcGuid))
		{
			GenericLOG(GenericLogExtraProc, Warning, TEXT("Auto launch extra start proc fail. Execute path : %s"), *ProcInfo.ExtraStartProcInfo.ProcFile.FilePath)
		}
	}
}
