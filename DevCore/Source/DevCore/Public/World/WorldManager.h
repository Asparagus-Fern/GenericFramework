// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelStreamingType.h"
#include "Manager/CoreManager.h"
#include "WorldManager.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UWorldManager : public UCoreManager
{
	GENERATED_BODY()

public:
	UWorldManager();

protected:
	void OnPostWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues InitializationValues);

	/* IProcedureBaseInterface */
public:
	virtual void NativeOnCreate() override;
	
	/* IProcedureInterface */
public:
	virtual void NativeOnActived() override;

	/* Level Streaming*/
public:
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, meta=(EditCondition = "!bIsWorldPartition", EditConditionHides))
	TArray<TSoftObjectPtr<UWorld>> AlwaysLoadLevels;

public:
	UFUNCTION(BlueprintCallable, Category="WorldManager|LevelStreaming")
	void LoadLevel(TSoftObjectPtr<UWorld> Level, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, FOnFinish OnFinish);

	UFUNCTION(BlueprintCallable, Category="WorldManager|LevelStreaming")
	void LoadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, FOnOnceFinish OnOnceFinish, FOnFinish OnFinish);

	UFUNCTION(BlueprintCallable, Category="WorldManager|LevelStreaming")
	void LoadLevelsBySetting(TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings, FOnOnceFinish OnOnceFinish, FOnFinish OnFinish);

	UFUNCTION(BlueprintCallable, Category="WorldManager|LevelStreaming")
	void UnloadLevel(TSoftObjectPtr<UWorld> Level, bool bShouldBlockOnUnload, FOnFinish OnFinish);

	UFUNCTION(BlueprintCallable, Category="WorldManager|LevelStreaming")
	void UnloadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bShouldBlockOnUnload, FOnOnceFinish OnOnceFinish, FOnFinish OnFinish);

	UFUNCTION(BlueprintCallable, Category="WorldManager|LevelStreaming")
	void UnloadLevelsBySetting(TArray<FUnloadLevelStreamingSetting> UnloadLevelStreamingSettings, FOnOnceFinish OnOnceFinish, FOnFinish OnFinish);

	UFUNCTION(BlueprintCallable, Category="WorldManager|LevelStreaming")
	void SetLevelVisibility(TSoftObjectPtr<UWorld> Level, bool bVisible, FOnFinish OnFinish);

	UFUNCTION(BlueprintCallable, Category="WorldManager|LevelStreaming")
	void SetLevelsVisibility(TArray<TSoftObjectPtr<UWorld>> Levels, bool bVisible, FOnOnceFinish OnOnceFinish, FOnFinish OnFinish);

public:
	/* 加载当前世界的所有流关卡(只加载不显示) */
	UFUNCTION(BlueprintCallable, Category="WorldManager|LevelStreaming")
	void LoadCurrentWorldLevelStreaming(FOnOnceFinish OnOnceFinish, FOnFinish OnFinish);

	/* 卸载当前世界的所有流关卡 */
	UFUNCTION(BlueprintCallable, Category="WorldManager|LevelStreaming")
	void UnLoadCurrentWorldLevelStreaming(FOnOnceFinish OnOnceFinish, FOnFinish OnFinish);

	/* 当前世界是否包含指定关卡 */
	UFUNCTION(BlueprintPure, Category="WorldManager|LevelStreaming")
	bool IsCurrentWorldContainLevel(const TSoftObjectPtr<UWorld>& Level) const;

	UFUNCTION(BlueprintCallable, Category="WorldManager|LevelStreaming")
	bool CheckLevel(TSoftObjectPtr<UWorld> Level);

	UFUNCTION(BlueprintCallable, Category="WorldManager|LevelStreaming")
	ULevelStreaming* GetLevelStreaming(TSoftObjectPtr<UWorld> Level);
};
