// Copyright ChenTaiye 2025. All Rights Reserved.

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
	void Initialize(const FUnloadLevelStreamingSetting& InSetting, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish);
	void Initialize(TArray<FUnloadLevelStreamingSetting> InSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish, const FOnHandleLevelStreamingFinish& OnFinish);

	/* ULevelStreamingHandle */
public:
	virtual void RemoveLevel(TSoftObjectPtr<UWorld> InLevel) override;
	virtual TArray<TSoftObjectPtr<UWorld>> GetLevels() override;
	virtual void ExecuteHandle(int32 Index) override;

	virtual void HandleOnOnceFinish() override;
	virtual void HandleOnFinish() override;

	/* UUnLoadLevelStreamingHandle */
public:
	TArray<FUnloadLevelStreamingSetting>& GetUnLoadLevelStreamingSettings() { return UnLoadLevelStreamingSettings; }

private:
	TArray<FUnloadLevelStreamingSetting> UnLoadLevelStreamingSettings;
	FOnHandleLevelStreamingOnceFinish OnUnLoadLevelStreamingOnceFinish;
	FOnHandleLevelStreamingFinish OnUnLoadLevelStreamingFinish;
	void UnLoadLevel(const TSoftObjectPtr<UWorld>& Level, const bool bShouldBlockOnUnload);
};
