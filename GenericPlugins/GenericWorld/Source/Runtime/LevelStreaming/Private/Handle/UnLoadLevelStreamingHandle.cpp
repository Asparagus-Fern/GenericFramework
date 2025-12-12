// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Handle/UnLoadLevelStreamingHandle.h"

#include "BPFunctions_LevelStreaming.h"
#include "Kismet/GameplayStatics.h"

void UUnLoadLevelStreamingHandle::Initialize(const FUnloadLevelStreamingSetting& InSetting, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	Initialize(TArray<FUnloadLevelStreamingSetting>{InSetting}, OnOnceFinish, OnFinish);
}

void UUnLoadLevelStreamingHandle::Initialize(TArray<FUnloadLevelStreamingSetting> InSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish)
{
	for (auto& Setting : InSettings)
	{
		if (Setting.IsValid() && !UnLoadLevelStreamingSettings.Contains(Setting))
		{
			UnLoadLevelStreamingSettings.Add(Setting);
		}
	}

	OnUnLoadLevelStreamingOnceFinish = OnOnceFinish;
	OnUnLoadLevelStreamingFinish = OnFinish;
}

void UUnLoadLevelStreamingHandle::RemoveLevel(TSoftObjectPtr<UWorld> InLevel)
{
	const int32 Index = GetIndexByLevel(InLevel);
	if (Index > GetLevelIndex())
	{
		if (const FUnloadLevelStreamingSetting* Found = UnLoadLevelStreamingSettings.FindByKey(InLevel))
		{
			UnLoadLevelStreamingSettings.Remove(*Found);
		}
	}
}

TArray<TSoftObjectPtr<UWorld>> UUnLoadLevelStreamingHandle::GetLevels()
{
	TArray<TSoftObjectPtr<UWorld>> HandleLevels;

	for (auto& Setting : UnLoadLevelStreamingSettings)
	{
		HandleLevels.Add(Setting.Level);
	}

	return HandleLevels;
}

void UUnLoadLevelStreamingHandle::ExecuteHandle(int32 Index)
{
	if (!UBPFunctions_LevelStreaming::IsLevelLoaded(this, UnLoadLevelStreamingSettings[Index].Level))
	{
		OnOnceFinish();
		return;
	}

	UnLoadLevel(UnLoadLevelStreamingSettings[Index].Level, UnLoadLevelStreamingSettings[Index].bShouldBlockOnUnload);
}

void UUnLoadLevelStreamingHandle::HandleOnOnceFinish()
{
	Super::HandleOnOnceFinish();
	OnUnLoadLevelStreamingOnceFinish.ExecuteIfBound();
}

void UUnLoadLevelStreamingHandle::HandleOnFinish()
{
	Super::HandleOnFinish();
	OnUnLoadLevelStreamingFinish.ExecuteIfBound();
}

void UUnLoadLevelStreamingHandle::UnLoadLevel(const TSoftObjectPtr<UWorld>& Level, const bool bShouldBlockOnUnload)
{
	const FLatentActionInfo LatentActionInfo(FMath::Rand(), FMath::Rand(), TEXT("OnOnceFinish"), this);
	UGameplayStatics::UnloadStreamLevelBySoftObjectPtr(this, Level, LatentActionInfo, bShouldBlockOnUnload);
}
