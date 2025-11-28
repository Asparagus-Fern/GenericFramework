// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SessionAsyncActionBase.h"
#include "EndSessionAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndSessionSuccess);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndSessionFail);

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API UEndSessionAsyncAction : public USessionAsyncActionBase
{
	GENERATED_UCLASS_BODY()

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
	FOnEndSessionCompleteDelegate OnEndSessionCompleteDelegate;
	void OnEndSessionComplete(FName InSessionName, bool bWasSuccessful);

	UPROPERTY()
	FName SessionName = NAME_None;
};
