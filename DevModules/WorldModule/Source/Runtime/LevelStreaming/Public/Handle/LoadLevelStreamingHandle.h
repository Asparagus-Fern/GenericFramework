// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LevelStreamingHandle.h"
#include "LevelStreamingType.h"
#include "LoadLevelStreamingHandle.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class ULoadLevelStreamingHandle : public ULevelStreamingHandle
{
	GENERATED_BODY()

	/* ULoadLevelStreamingHandle */
public:
	void Initialize(const FLoadLevelStreamingSetting& InSetting);
	void Initialize(TArray<FLoadLevelStreamingSetting> InSettings);

	/* ULevelStreamingHandle */
public:
	virtual void RemoveLevel(TSoftObjectPtr<UWorld> InLevel) override;
	virtual TArray<TSoftObjectPtr<UWorld>> GetLevels() override;
	virtual void ExecuteHandle(int32 Index) override;

	/* ULoadLevelStreamingHandle */
public:
	TArray<FLoadLevelStreamingSetting>& GetLoadLevelStreamingSettings() { return LoadLevelStreamingSettings; }

private:
	TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings;
	void LoadLevel(const TSoftObjectPtr<UWorld>& Level, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad);
};
