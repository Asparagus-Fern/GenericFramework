// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelStreamingType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_LevelStreaming.generated.h"

/**
 * 
 */
UCLASS()
class LEVELSTREAMING_API UBPFunctions_LevelStreaming : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_DELEGATE(FHandleLevelStreamingOnceFinish);

	DECLARE_DYNAMIC_DELEGATE(FHandleLevelStreamingFinish);

public:
	UFUNCTION(BlueprintCallable)
	static void LoadLevel(TSoftObjectPtr<UWorld> Level, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable)
	static void LoadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable)
	static void LoadLevelsBySetting(TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable)
	static void UnloadLevel(TSoftObjectPtr<UWorld> Level, bool bShouldBlockOnUnload, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable)
	static void UnloadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bShouldBlockOnUnload, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable)
	static void UnloadLevelsBySetting(TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable)
	static void SetLevelVisibility(TSoftObjectPtr<UWorld> Level, bool bVisible, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable)
	static void SetLevelsVisibility(TArray<TSoftObjectPtr<UWorld>> Levels, bool bVisible, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish);

public:
	UFUNCTION(BlueprintCallable)
	static void LoadCurrentWorldLevelStreaming(FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable)
	static void UnLoadCurrentWorldLevelStreaming(FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish);

public:
	UFUNCTION(BlueprintPure)
	static bool IsCurrentWorldContainLevel(TSoftObjectPtr<UWorld> Level, bool& Contain);
};
