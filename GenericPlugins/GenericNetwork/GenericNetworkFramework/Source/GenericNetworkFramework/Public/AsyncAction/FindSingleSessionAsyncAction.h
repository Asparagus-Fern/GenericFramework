// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SessionAsyncActionBase.h"
#include "FindSingleSessionAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFindSingleSessionSuccess, const FGenericSessionSearchResult&, SessionSearchResult);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFindSingleSessionFail);

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API UFindSingleSessionAsyncAction : public USessionAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Activate() override;

public:
	UFUNCTION(BlueprintCallable, Category="Generic Session", meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UFindSingleSessionAsyncAction* FindSingleSession(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerUniqueNetID, const FUniqueNetworkID& InSessionPlayerUniqueNetID);

public:
	UPROPERTY(BlueprintAssignable)
	FFindSingleSessionSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFindSingleSessionFail OnFail;

private:
	FOnSingleSessionResultCompleteDelegate OnSingleSessionResultCompleteDelegate;
	void OnFindSessionComplete(int32 InPlayerIndex, bool bWasSuccessful, const FOnlineSessionSearchResult& InResult);

	UPROPERTY()
	FUniqueNetworkID PlayerUniqueNetID;

	UPROPERTY()
	FUniqueNetworkID SessionPlayerUniqueNetID;
};
