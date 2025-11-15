// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "EndSessionAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndSessionSuccess);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndSessionFail);

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API UEndSessionAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

public:
	UFUNCTION(BlueprintCallable, Category="Generic Session", meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UEndSessionAsyncAction* EndSession(UObject* InWorldContextObject, FName InSessionName);

public:
	UPROPERTY(BlueprintAssignable)
	FEndSessionSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FEndSessionFail OnFail;

private:
	void OnEndSessionComplete(FName InSessionName, bool bWasSuccessful);

	UPROPERTY()
	UObject* WorldContextObject = nullptr;

	UPROPERTY()
	FName SessionName = NAME_None;
};
