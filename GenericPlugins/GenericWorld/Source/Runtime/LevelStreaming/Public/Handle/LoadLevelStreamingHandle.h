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
	void Initialize(const FLoadLevelStreamingSetting& InSetting, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish);
	void Initialize(TArray<FLoadLevelStreamingSetting> InSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish);

	/* ULevelStreamingHandle */
public:
	virtual void RemoveLevel(TSoftObjectPtr<UWorld> InLevel) override;
	virtual TArray<TSoftObjectPtr<UWorld>> GetLevels() override;
	virtual void ExecuteHandle(int32 Index) override;

	virtual void HandleOnOnceFinish() override;
	virtual void HandleOnFinish() override;

	/* ULoadLevelStreamingHandle */
public:
	TArray<FLoadLevelStreamingSetting>& GetLoadLevelStreamingSettings() { return LoadLevelStreamingSettings; }

private:
	TArray<FLoadLevelStreamingSetting> LoadLevelStreamingSettings;
	FOnHandleLevelStreamingOnceFinish OnLoadLevelStreamingOnceFinish;
	FOnHandleLevelStreamingFinish OnLoadLevelStreamingFinish;
	void LoadLevel(const TSoftObjectPtr<UWorld>& Level, const bool bMakeVisibleAfterLoad, const bool bShouldBlockOnLoad);
};
