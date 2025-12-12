// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LevelStreamingType.h"
#include "Subsystem/GenericWorldSubsystem.h"
#include "LevelStreamingSubsystem.generated.h"

class USetLevelStreamingVisibilityHandle;
class UUnLoadLevelStreamingHandle;
class ULoadLevelStreamingHandle;
class ULevelStreamingHandle;

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnLoadLevelStreamingHandleRegister, ULoadLevelStreamingHandle*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnLoadLevelStreamingHandleRegister, ULoadLevelStreamingHandle*, InHandle);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnUnLoadLevelStreamingHandleRegister, UUnLoadLevelStreamingHandle*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnUnLoadLevelStreamingHandleRegister, UUnLoadLevelStreamingHandle*, InHandle);

DECLARE_MULTICAST_DELEGATE_OneParam(FDelegate_OnSetLevelStreamingVisibilityHandleRegister, USetLevelStreamingVisibilityHandle*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBPDelegate_OnSetLevelStreamingVisibilityHandleRegister, USetLevelStreamingVisibilityHandle*, InHandle);

/**
 * 
 */
UCLASS(MinimalAPI)
class ULevelStreamingSubsystem : public UGenericWorldSubsystem
{
	GENERATED_BODY()

public:
	static LEVELSTREAMING_API ULevelStreamingSubsystem* Get(const UObject* WorldContextObject);
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/* ULevelStreamingSubsystem */
public:
	LEVELSTREAMING_API ULoadLevelStreamingHandle* LoadLevel(const TSoftObjectPtr<UWorld>& Level, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API ULoadLevelStreamingHandle* LoadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API ULoadLevelStreamingHandle* LoadLevelsBySetting(TArray<FLoadLevelStreamingSetting> InSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());

	LEVELSTREAMING_API UUnLoadLevelStreamingHandle* UnloadLevel(const TSoftObjectPtr<UWorld>& Level, bool bShouldBlockOnUnload, const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API UUnLoadLevelStreamingHandle* UnloadLevels(TArray<TSoftObjectPtr<UWorld>> Levels, bool bShouldBlockOnUnload, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API UUnLoadLevelStreamingHandle* UnloadLevelsBySetting(TArray<FUnloadLevelStreamingSetting> InSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());

	LEVELSTREAMING_API USetLevelStreamingVisibilityHandle* SetLevelVisibility(const TSoftObjectPtr<UWorld>& Level, bool bVisible, const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API USetLevelStreamingVisibilityHandle* SetLevelsVisibility(const TArray<TSoftObjectPtr<UWorld>>& Levels, bool bVisible, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API USetLevelStreamingVisibilityHandle* SetLevelsVisibilityBySetting(const TArray<FSetLevelStreamingVisibilitySetting>& InSettings, const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	
	LEVELSTREAMING_API TArray<TSoftObjectPtr<UWorld>> GetCurrentWorldLevelStreamingList() const;
	
	LEVELSTREAMING_API ULoadLevelStreamingHandle* LoadCurrentWorldLevelStreaming(const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());
	LEVELSTREAMING_API UUnLoadLevelStreamingHandle* UnLoadCurrentWorldLevelStreaming(const FOnHandleLevelStreamingOnceFinish& OnOnceFinish = FOnHandleLevelStreamingOnceFinish(), const FOnHandleLevelStreamingFinish& OnFinish = FOnHandleLevelStreamingFinish());

	LEVELSTREAMING_API ULevelStreaming* GetLevelStreaming(const TSoftObjectPtr<UWorld>& Level) const;
	LEVELSTREAMING_API bool IsCurrentWorldContainLevel(const TSoftObjectPtr<UWorld>& Level) const;

public:
	inline static FDelegate_OnLoadLevelStreamingHandleRegister Delegate_OnLoadLevelStreamingHandleRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnLoadLevelStreamingHandleRegister BPDelegate_OnLoadLevelStreamingHandleRegister;

	inline static FDelegate_OnUnLoadLevelStreamingHandleRegister Delegate_OnUnLoadLevelStreamingHandleRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnUnLoadLevelStreamingHandleRegister BPDelegate_OnUnLoadLevelStreamingHandleRegister;

	inline static FDelegate_OnSetLevelStreamingVisibilityHandleRegister Delegate_OnSetLevelStreamingVisibilityHandleRegister;
	UPROPERTY(BlueprintAssignable)
	FBPDelegate_OnSetLevelStreamingVisibilityHandleRegister BPDelegate_OnSetLevelStreamingVisibilityHandleRegister;

protected:
	void CheckConflictLevelStreamHandle(TArray<FLoadLevelStreamingSetting>& InSettings) const;
	void CheckConflictLevelStreamHandle(TArray<FUnloadLevelStreamingSetting>& InSettings) const;
	void CheckConflictLevelStreamHandle(TArray<FSetLevelStreamingVisibilitySetting>& InSettings) const;

	void OnHandleLevelOnceFinish(ULevelStreamingHandle* InHandle, TSoftObjectPtr<UWorld> InLevel);
	void OnHandleLevelFinish(ULevelStreamingHandle* InHandle);

private:
	TArray<TObjectPtr<ULevelStreamingHandle>> LevelStreamingHandles;
};
