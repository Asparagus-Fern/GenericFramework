// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LevelStreamingType.h"
#include "Interface/ManagerInterface.h"
#include "LevelStreamingManager.generated.h"

class USetLevelStreamingVisibilityHandle;
class UUnLoadLevelStreamingHandle;
class ULoadLevelStreamingHandle;
class ULevelStreamingHandle;

/**
 * 
 */
UCLASS(MinimalAPI)
class ULevelStreamingManager : public UWorldSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

	/* ULevelStreamingManager */
public:
	LEVELSTREAMING_API ULoadLevelStreamingHandle* LoadLevel(const TSoftObjectPtr<UWorld>& Level, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API ULoadLevelStreamingHandle* LoadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API ULoadLevelStreamingHandle* LoadLevelsBySetting(TArray<FLoadLevelStreamingSetting> InSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());

	LEVELSTREAMING_API UUnLoadLevelStreamingHandle* UnloadLevel(const TSoftObjectPtr<UWorld>& Level, bool bShouldBlockOnUnload, const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API UUnLoadLevelStreamingHandle* UnloadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bShouldBlockOnUnload, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API UUnLoadLevelStreamingHandle* UnloadLevelsBySetting(TArray<FUnloadLevelStreamingSetting> InSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());

	LEVELSTREAMING_API USetLevelStreamingVisibilityHandle* SetLevelVisibility(const TSoftObjectPtr<UWorld>& Level, bool bVisible, const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API USetLevelStreamingVisibilityHandle* SetLevelsVisibility(TArray<TSoftObjectPtr<UWorld>> Levels, bool bVisible, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API USetLevelStreamingVisibilityHandle* SetLevelsVisibilityBySetting(TArray<FSetLevelStreamingVisibilitySetting> InSettings, FOnHandleLevelStreamingOnceFinish OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), FOnHandleLevelStreamingFinish OnFinish = FOnHandleLevelStreamingFinish());

	LEVELSTREAMING_API ULoadLevelStreamingHandle* LoadCurrentWorldLevelStreaming(const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API UUnLoadLevelStreamingHandle* UnLoadCurrentWorldLevelStreaming(const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());

	LEVELSTREAMING_API ULevelStreaming* GetLevelStreaming(TSoftObjectPtr<UWorld> Level) const;
	LEVELSTREAMING_API bool IsCurrentWorldContainLevel(const TSoftObjectPtr<UWorld>& Level) const;

protected:
	void CheckConflictLevelStreamHandle(TArray<FLoadLevelStreamingSetting>& InSettings) const;
	void CheckConflictLevelStreamHandle(TArray<FUnloadLevelStreamingSetting>& InSettings) const;
	void CheckConflictLevelStreamHandle(TArray<FSetLevelStreamingVisibilitySetting>& InSettings) const;

	void OnHandleLevelOnceFinish(ULevelStreamingHandle* InHandle, TSoftObjectPtr<UWorld> InLevel);
	void OnHandleLevelFinish(ULevelStreamingHandle* InHandle);

private:
	TArray<TObjectPtr<ULevelStreamingHandle>> LevelStreamingHandles;
};
