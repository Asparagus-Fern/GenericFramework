// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "StartSessionAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartSessionSuccess);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartSessionFail);

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API UStartSessionAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

public:
	UFUNCTION(BlueprintCallable, Category="Generic Session", meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UStartSessionAsyncAction* StartSession(UObject* InWorldContextObject, FName InSessionName);

public:
	UPROPERTY(BlueprintAssignable)
	FStartSessionSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FStartSessionFail OnFail;

private:
	void OnStartSessionComplete(FName InSessionName, bool bWasSuccessful);

	UPROPERTY()
	UObject* WorldContextObject = nullptr;

	UPROPERTY()
	FName SessionName = NAME_None;
};
