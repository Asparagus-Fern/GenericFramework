// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "HandleLevelAsyncAction.generated.h"

/**
 * 
 */
UCLASS()
class LEVELSTREAMING_API UHandleLevelAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true"))
	static UHandleLevelAsyncAction* LoadLevel( TSoftObjectPtr<UWorld> Level, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad);

	UFUNCTION(BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true"))
	static UHandleLevelAsyncAction* UnloadLevel( TSoftObjectPtr<UWorld> Level, bool bShouldBlockOnUnload);

	UFUNCTION(BlueprintCallable, meta = ( BlueprintInternalUseOnly = "true"))
	static UHandleLevelAsyncAction* SetLevelVisibility( TSoftObjectPtr<UWorld> Level, bool bVisible);

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHandleLevelFinish);

	UPROPERTY(BlueprintAssignable)
	FHandleLevelFinish OnFinish;

protected:
	void OnHandleFinish() const;
};
