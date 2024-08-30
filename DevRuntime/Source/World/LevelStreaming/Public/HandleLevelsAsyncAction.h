// Fill out your copyright notice in the Description page of Project Settings.

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
	UFUNCTION(BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* LoadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad);

	UFUNCTION(BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* LoadLevelsBySetting(TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings);

	UFUNCTION(BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* UnloadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bShouldBlockOnUnload);

	UFUNCTION(BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* UnloadLevelsBySetting(TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings);

	UFUNCTION(BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* SetLevelsVisibility(TArray<TSoftObjectPtr<UWorld>> Levels, bool bVisible);

public:
	UFUNCTION(BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* LoadCurrentWorldLevelStreaming();

	UFUNCTION(BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true"))
	static UHandleLevelsAsyncAction* UnLoadCurrentWorldLevelStreaming();

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
