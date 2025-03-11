// Fill out your copyright notice in the Description page of Project Settings.


#include "Handle/LoadLevelStreamingHandle.h"

#include "BPFunctions_LevelStreaming.h"
#include "Kismet/GameplayStatics.h"

void ULoadLevelStreamingHandle::Initialize(const FLoadLevelStreamingSetting& InSetting)
{
	Initialize(TArray<FLoadLevelStreamingSetting>{InSetting});
}

void ULoadLevelStreamingHandle::Initialize(TArray<FLoadLevelStreamingSetting> InSettings)
{
	for (auto& Setting : InSettings)
	{
		if (Setting.IsValid() && !LoadLevelStreamingSettings.Contains(Setting))
		{
			LoadLevelStreamingSettings.Add(Setting);
		}
	}
}

void ULoadLevelStreamingHandle::RemoveLevel(TSoftObjectPtr<UWorld> InLevel)
{
	const int32 Index = GetIndexByLevel(InLevel);
	if (Index > GetLevelIndex())
	{
		if (const FLoadLevelStreamingSetting* Found = LoadLevelStreamingSettings.FindByKey(InLevel))
		{
			LoadLevelStreamingSettings.Remove(*Found);
		}
	}
}

TArray<TSoftObjectPtr<UWorld>> ULoadLevelStreamingHandle::GetLevels()
{
	TArray<TSoftObjectPtr<UWorld>> HandleLevels;

	for (auto& Setting : LoadLevelStreamingSettings)
	{
		HandleLevels.Add(Setting.Level);
	}

	return HandleLevels;
}

void ULoadLevelStreamingHandle::ExecuteHandle(int32 Index)
{
	if (UBPFunctions_LevelStreaming::IsLevelLoaded(LoadLevelStreamingSettings[Index].Level))
	{
		OnOnceFinish();
		return;
	}

	LoadLevel(LoadLevelStreamingSettings[Index].Level, LoadLevelStreamingSettings[Index].bMakeVisibleAfterLoad, LoadLevelStreamingSettings[Index].bShouldBlockOnLoad);
}

void ULoadLevelStreamingHandle::LoadLevel(const TSoftObjectPtr<UWorld>& Level, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad)
{
	const FLatentActionInfo LatentActionInfo(FMath::Rand(), FMath::Rand(), TEXT("OnOnceFinish"), this);
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, Level, bMakeVisibleAfterLoad, bShouldBlockOnLoad, LatentActionInfo);
}
