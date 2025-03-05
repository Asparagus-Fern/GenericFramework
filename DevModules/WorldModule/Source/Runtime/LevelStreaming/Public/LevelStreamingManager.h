// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelStreamingType.h"
#include "Manager/CoreInternalManager.h"
#include "LevelStreamingManager.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class ULevelStreamingManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* ULevelStreamingManager */
public:
	LEVELSTREAMING_API void LoadLevel(const TSoftObjectPtr<UWorld>& Level, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API void LoadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API void LoadLevelsBySetting(TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());

	LEVELSTREAMING_API void UnloadLevel(const TSoftObjectPtr<UWorld>& Level, bool bShouldBlockOnUnload, const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API void UnloadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bShouldBlockOnUnload, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API void UnloadLevelsBySetting(TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());

	LEVELSTREAMING_API void SetLevelVisibility(const TSoftObjectPtr<UWorld>& Level, bool bVisible, const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API void SetLevelsVisibility(TArray<TSoftObjectPtr<UWorld>> Levels, bool bVisible, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());

public:
	LEVELSTREAMING_API void LoadCurrentWorldLevelStreaming(const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API void UnLoadCurrentWorldLevelStreaming(const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());

	LEVELSTREAMING_API bool IsCurrentWorldContainLevel(const TSoftObjectPtr<UWorld>& Level) const;

protected:
	bool CheckLevel(const TSoftObjectPtr<UWorld>& Level) const;
	ULevelStreaming* GetLevelStreaming(const TSoftObjectPtr<UWorld>& Level) const;
};
