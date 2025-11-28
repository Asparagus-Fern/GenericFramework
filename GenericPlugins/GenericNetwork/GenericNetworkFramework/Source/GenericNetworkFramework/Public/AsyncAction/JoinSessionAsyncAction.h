// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NetworkType.h"
#include "SessionAsyncActionBase.h"
#include "JoinSessionAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FJoinSessionComplete, EJoinSessionResult, Result);

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API UJoinSessionAsyncAction : public USessionAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Activate() override;

public:
	UFUNCTION(BlueprintCallable, Category="Generic Session", meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UJoinSessionAsyncAction* JoinSession(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, const FGenericSessionSearchResult& InSessionSearchResult);

public:
	UPROPERTY(BlueprintAssignable)
	FJoinSessionComplete OnComplete;

private:
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;
	void OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type Result);

	UPROPERTY()
	FUniqueNetworkID UniqueNetID;

	UPROPERTY()
	FGenericSessionSearchResult SessionSearchResult;
};
