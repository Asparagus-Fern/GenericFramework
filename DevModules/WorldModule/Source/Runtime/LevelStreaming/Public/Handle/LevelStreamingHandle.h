// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Handle/HandleBase.h"
#include "LevelStreamingHandle.generated.h"

class ULevelStreamingHandle;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnLevelStreamingHandleOnceFinish, ULevelStreamingHandle*, TSoftObjectPtr<UWorld>)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLevelStreamingHandleFinish, ULevelStreamingHandle*)

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class ULevelStreamingHandle : public UHandleBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void Startup();

	UFUNCTION(BlueprintPure)
	int32 GetLevelIndex() const;

	UFUNCTION(BlueprintPure)
	TSoftObjectPtr<UWorld> GetLevelByIndex(int32 InIndex);

	UFUNCTION(BlueprintPure)
	int32 GetIndexByLevel(const TSoftObjectPtr<UWorld>& InLevel);
	
	UFUNCTION(BlueprintCallable)
	virtual void RemoveLevel(TSoftObjectPtr<UWorld> InLevel) PURE_VIRTUAL(, ;)

	UFUNCTION(BlueprintPure)
	virtual TArray<TSoftObjectPtr<UWorld>> GetLevels() PURE_VIRTUAL(, return TArray<TSoftObjectPtr<UWorld>>{};)

	UFUNCTION()
	virtual void ExecuteHandle(int32 Index) PURE_VIRTUAL(,)
	
protected:
	UFUNCTION()
	virtual void OnOnceFinish();

	UFUNCTION()
	virtual void OnFinish();

public:
	FOnLevelStreamingHandleOnceFinish& GetHandleOnceFinishEvent();
	FOnLevelStreamingHandleFinish& GetHandleFinishEvent();

protected:
	void BroadcastOnceFinish();
	void BroadcastFinish();

private:
	int32 LevelIndex = 0;
	FOnLevelStreamingHandleOnceFinish OnOnceFinishEvent;
	FOnLevelStreamingHandleFinish OnFinishEvent;
};
