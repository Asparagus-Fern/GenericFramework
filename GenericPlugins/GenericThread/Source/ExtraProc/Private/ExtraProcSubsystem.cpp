// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ExtraProcSubsystem.h"

#include "ExtraProcSettings.h"
#include "StaticFunctions_ExtraProc.h"
#include "GenericThreadSubsystem.h"
#include "BPFunctions/BPFunctions_File.h"
#include "Async/TaskGraphInterfaces.h"
#include "Async/Async.h"
#include "Type/DebugType.h"

#if PLATFORM_WINDOWS
#include "Platform/WindowsExtraProcHelper.h"
#endif

#if WITH_EDITOR
#include "Editor.h"
#endif

UExtraProcSubsystem* UExtraProcSubsystem::Get()
{
	return GEngine->GetEngineSubsystem<UExtraProcSubsystem>();
}

void UExtraProcSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

#if WITH_EDITOR
	FEditorDelegates::BeginPIE.AddUObject(this, &UExtraProcSubsystem::BeginPIE);
#else
	LaunchAllProc();
#endif

	if (!FPaths::DirectoryExists(GetExtrasPath()))
	{
		UBPFunctions_File::CreateDirectory(GetExtrasPath());
	}
}

void UExtraProcSubsystem::Deinitialize()
{
	Super::Deinitialize();

#if WITH_EDITOR
	FEditorDelegates::BeginPIE.RemoveAll(this);
#endif
}

#if WITH_EDITOR

void UExtraProcSubsystem::BeginPIE(bool bIsSimulating)
{
	LaunchAllProc();
}

#endif

void UExtraProcSubsystem::LaunchAllProc()
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

FString UExtraProcSubsystem::GetExtrasPath()
{
	return FPaths::Combine(FPaths::ProjectDir(), TEXT("Extras"));
}
