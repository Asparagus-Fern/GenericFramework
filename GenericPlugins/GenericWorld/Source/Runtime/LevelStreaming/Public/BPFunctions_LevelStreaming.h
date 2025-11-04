// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LevelStreamingType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_LevelStreaming.generated.h"

DECLARE_DYNAMIC_DELEGATE(FHandleLevelStreamingOnceFinish);

DECLARE_DYNAMIC_DELEGATE(FHandleLevelStreamingFinish);

/**
 * 
 */
UCLASS()
class LEVELSTREAMING_API UBPFunctions_LevelStreaming : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void LoadLevel(const UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void LoadLevels(const UObject* WorldContextObject, TArray<TSoftObjectPtr<UWorld>> Levels, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void LoadLevelsBySetting(const UObject* WorldContextObject, TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void UnloadLevel(const UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level, bool bShouldBlockOnUnload, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void UnloadLevels(const UObject* WorldContextObject, TArray<TSoftObjectPtr<UWorld>> Levels, bool bShouldBlockOnUnload, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void UnloadLevelsBySetting(const UObject* WorldContextObject, TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void SetLevelVisibility(const UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level, bool bVisible, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void SetLevelsVisibility(const UObject* WorldContextObject, TArray<TSoftObjectPtr<UWorld>> Levels, bool bVisible, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish);

public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void LoadCurrentWorldLevelStreaming(const UObject* WorldContextObject, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void UnLoadCurrentWorldLevelStreaming(const UObject* WorldContextObject, FHandleLevelStreamingOnceFinish OnOnceFinish, FHandleLevelStreamingFinish OnFinish);

public:
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static ULevelStreaming* GetLevelStreaming(const UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static bool IsLevelLoaded(const UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static bool IsCurrentWorldContainLevel(const UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level, bool& Contain);
};
