// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelStreamingType.h"
#include "Manager/CoreManager.h"
#include "LevelStreamingManager.generated.h"

/**
 * 
 */
UCLASS()
class LEVELSTREAMING_API ULevelStreamingManager : public UCoreManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;
	virtual void NativeOnInactived() override;

	/* ULevelStreamingManager */
public:
	void LoadLevel(const TSoftObjectPtr<UWorld>& Level, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	void LoadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	void LoadLevelsBySetting(TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());

	void UnloadLevel(const TSoftObjectPtr<UWorld>& Level, bool bShouldBlockOnUnload, const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	void UnloadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bShouldBlockOnUnload, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	void UnloadLevelsBySetting(TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());

	void SetLevelVisibility(const TSoftObjectPtr<UWorld>& Level, bool bVisible, const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	void SetLevelsVisibility(TArray<TSoftObjectPtr<UWorld>> Levels, bool bVisible, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());

public:
	void LoadCurrentWorldLevelStreaming(const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	void UnLoadCurrentWorldLevelStreaming(const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());

	bool IsCurrentWorldContainLevel(const TSoftObjectPtr<UWorld>& Level) const;

protected:
	bool CheckLevel(const TSoftObjectPtr<UWorld>& Level) const;
	ULevelStreaming* GetLevelStreaming(const TSoftObjectPtr<UWorld>& Level) const;
};
