// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Handle/LoadLevelStreamingHandle.h"

#include "BPFunctions_LevelStreaming.h"
#include "Kismet/GameplayStatics.h"

void ULoadLevelStreamingHandle::Initialize(const FLoadLevelStreamingSetting& InSetting, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	Initialize(TArray<FLoadLevelStreamingSetting>{InSetting}, OnOnceFinish, OnFinish);
}

void ULoadLevelStreamingHandle::Initialize(TArray<FLoadLevelStreamingSetting> InSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	for (auto& Setting : InSettings)
	{
		if (Setting.IsValid() && !LoadLevelStreamingSettings.Contains(Setting))
		{
			LoadLevelStreamingSettings.Add(Setting);
		}
	}

	OnLoadLevelStreamingOnceFinish = OnOnceFinish;
	OnLoadLevelStreamingFinish = OnFinish;
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
	if (UBPFunctions_LevelStreaming::IsLevelLoaded(this, LoadLevelStreamingSettings[Index].Level))
	{
		OnOnceFinish();
		return;
	}

	LoadLevel(LoadLevelStreamingSettings[Index].Level, LoadLevelStreamingSettings[Index].bMakeVisibleAfterLoad, LoadLevelStreamingSettings[Index].bShouldBlockOnLoad);
}

void ULoadLevelStreamingHandle::HandleOnOnceFinish()
{
	Super::HandleOnOnceFinish();
	OnLoadLevelStreamingOnceFinish.ExecuteIfBound();
}

void ULoadLevelStreamingHandle::HandleOnFinish()
{
	Super::HandleOnFinish();
	OnLoadLevelStreamingFinish.ExecuteIfBound();
}

void ULoadLevelStreamingHandle::LoadLevel(const TSoftObjectPtr<UWorld>& Level, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad)
{
	const FLatentActionInfo LatentActionInfo(FMath::Rand(), FMath::Rand(), TEXT("OnOnceFinish"), this);
	UGameplayStatics::LoadStreamLevelBySoftObjectPtr(this, Level, bMakeVisibleAfterLoad, bShouldBlockOnLoad, LatentActionInfo);
}
