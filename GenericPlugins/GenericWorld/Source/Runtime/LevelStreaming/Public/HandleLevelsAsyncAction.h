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
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* AsyncLoadLevels(const UObject* WorldContextObject, TArray<TSoftObjectPtr<UWorld>> Levels, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* AsyncLoadLevelsBySetting(const UObject* WorldContextObject, TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* AsyncUnloadLevels(const UObject* WorldContextObject, TArray<TSoftObjectPtr<UWorld>> Levels, bool bShouldBlockOnUnload);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* AsyncUnloadLevelsBySetting(const UObject* WorldContextObject, TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* AsyncSetLevelsVisibility(const UObject* WorldContextObject, TArray<TSoftObjectPtr<UWorld>> Levels, bool bVisible);

public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* AsyncLoadCurrentWorldLevelStreaming(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* AsyncUnLoadCurrentWorldLevelStreaming(const UObject* WorldContextObject);

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
