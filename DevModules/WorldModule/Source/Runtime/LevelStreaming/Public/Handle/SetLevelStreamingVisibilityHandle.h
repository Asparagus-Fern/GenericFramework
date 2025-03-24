// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LevelStreamingHandle.h"
#include "LevelStreamingType.h"
#include "SetLevelStreamingVisibilityHandle.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class USetLevelStreamingVisibilityHandle : public ULevelStreamingHandle
{
	GENERATED_BODY()

	/* ULoadLevelStreamingHandle */
public:
	void Initialize(const FSetLevelStreamingVisibilitySetting& InSetting);
	void Initialize(TArray<FSetLevelStreamingVisibilitySetting> InSettings);

	/* ULevelStreamingHandle */
public:
	virtual void RemoveLevel(TSoftObjectPtr<UWorld> InLevel) override;
	virtual TArray<TSoftObjectPtr<UWorld>> GetLevels() override;
	virtual void ExecuteHandle(int32 Index) override;

	/* ULoadLevelStreamingHandle */
public:
	TArray<FSetLevelStreamingVisibilitySetting>& GetSetLevelStreamingVisibilitySettings() { return SetLevelStreamingVisibilitySettings; }

private:
	TArray<FSetLevelStreamingVisibilitySetting> SetLevelStreamingVisibilitySettings;

	void LoadLevelsBeforeSetVisibility();
	void SetLevelVisibility(const TSoftObjectPtr<UWorld>& Level, const bool bVisible);

	UFUNCTION()
	void OnLevelVisibilityChanged();
};
