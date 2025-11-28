// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "NetworkType.h"
#include "SessionAsyncActionBase.h"
#include "FindSessionAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFindSessionSuccess, const TArray<FGenericSessionSearchResult>&, SessionSearchResults);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFindSessionFail);

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API UFindSessionAsyncAction : public USessionAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Activate() override;

public:
	UFUNCTION(BlueprintCallable, Category="Generic Session", meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UFindSessionAsyncAction* FindSessions(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, const FGenericSessionSearchSettings& InSessionSearchSettings);

public:
	UPROPERTY(BlueprintAssignable)
	FFindSessionSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFindSessionFail OnFail;

private:
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;
	void OnFindSessionsComplete(bool bWasSuccessful);

	UPROPERTY()
	FUniqueNetworkID UniqueNetID;

	UPROPERTY()
	FGenericSessionSearchSettings SessionSearchSettings;

	UPROPERTY()
	TArray<FGenericSessionSearchResult> SessionSearchResults;
};
