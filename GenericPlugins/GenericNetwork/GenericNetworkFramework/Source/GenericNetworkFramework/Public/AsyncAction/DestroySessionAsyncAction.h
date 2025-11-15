// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "DestroySessionAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDestroySessionSuccess);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDestroySessionFail);

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API UDestroySessionAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

public:
	UFUNCTION(BlueprintCallable, Category="Generic Session", meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UDestroySessionAsyncAction* DestroySession(UObject* InWorldContextObject, FName InSessionName);

public:
	UPROPERTY(BlueprintAssignable)
	FDestroySessionSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDestroySessionFail OnFail;

private:
	void OnDestroySessionComplete(FName InSessionName, bool bWasSuccessful);

	UPROPERTY()
	UObject* WorldContextObject = nullptr;

	UPROPERTY()
	FName SessionName = NAME_None;
};
