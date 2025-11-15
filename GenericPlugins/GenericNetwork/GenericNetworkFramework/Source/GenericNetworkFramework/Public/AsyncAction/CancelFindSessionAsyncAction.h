// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CancelFindSessionAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCancelFindSessionSuccess);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCancelFindSessionFail);

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API UCancelFindSessionAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

public:
	UFUNCTION(BlueprintCallable, Category="Generic Session", meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UCancelFindSessionAsyncAction* CancelFindSession(UObject* InWorldContextObject);

public:
	UPROPERTY(BlueprintAssignable)
	FCancelFindSessionSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCancelFindSessionFail OnFail;

private:
	void OnCancelFindSessionsComplete(bool bWasSuccessful);

	UPROPERTY()
	UObject* WorldContextObject = nullptr;
};
