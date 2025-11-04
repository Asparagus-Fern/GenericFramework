// Copyright ChenTaiye 2025. All Rights Reserved.

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
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UHandleLevelAsyncAction* LoadLevel(const UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UHandleLevelAsyncAction* UnloadLevel(const UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level, bool bShouldBlockOnUnload);

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UHandleLevelAsyncAction* SetLevelVisibility(const UObject* WorldContextObject, TSoftObjectPtr<UWorld> Level, bool bVisible);

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHandleLevelFinish);

	UPROPERTY(BlueprintAssignable)
	FHandleLevelFinish OnFinish;

protected:
	void OnHandleFinish() const;
};
