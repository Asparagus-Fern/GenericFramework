// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LevelStreamingType.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HandleLevelsAsyncAction.generated.h"

/**
 * 
 */
UCLASS()
class LEVELSTREAMING_API UHandleLevelsAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* AsyncLoadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* AsyncLoadLevelsBySetting(TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* AsyncUnloadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bShouldBlockOnUnload);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* AsyncUnloadLevelsBySetting(TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* AsyncSetLevelsVisibility(TArray<TSoftObjectPtr<UWorld>> Levels, bool bVisible);

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* AsyncLoadCurrentWorldLevelStreaming();

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* AsyncUnLoadCurrentWorldLevelStreaming();

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHandleLevelOnceFinish);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHandleLevelFinish);

	UPROPERTY(BlueprintAssignable)
	FHandleLevelOnceFinish OnOnceFinish;

	UPROPERTY(BlueprintAssignable)
	FHandleLevelFinish OnFinish;

protected:
	void OnHandleOnceFinish() const;
	void OnHandleFinish() const;
};
