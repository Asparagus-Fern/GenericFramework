// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelStreamingHandle.h"
#include "LevelStreamingType.h"
#include "UnLoadLevelStreamingHandle.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UUnLoadLevelStreamingHandle : public ULevelStreamingHandle
{
	GENERATED_BODY()

	/* UUnLoadLevelStreamingHandle */
public:
	void Initialize(const FUnloadLevelStreamingSetting& InSetting);
	void Initialize(TArray<FUnloadLevelStreamingSetting> InSettings);

	/* ULevelStreamingHandle */
public:
	virtual void RemoveLevel(TSoftObjectPtr<UWorld> InLevel) override;
	virtual TArray<TSoftObjectPtr<UWorld>> GetLevels() override;
	virtual void ExecuteHandle(int32 Index) override;

	/* UUnLoadLevelStreamingHandle */
public:
	TArray<FUnloadLevelStreamingSetting>& GetUnLoadLevelStreamingSettings() { return UnLoadLevelStreamingSettings; }

private:
	TArray<FUnloadLevelStreamingSetting> UnLoadLevelStreamingSettings;
	void UnLoadLevel(const TSoftObjectPtr<UWorld>& Level, const bool bShouldBlockOnUnload);
};
