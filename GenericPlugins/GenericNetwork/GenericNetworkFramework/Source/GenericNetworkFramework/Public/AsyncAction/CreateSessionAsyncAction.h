// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "SessionAsyncActionBase.h"
#include "CreateSessionAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreateSessionSuccess, const FGenericSessionSettings&, SessionSettings);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCreateSessionFail);

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API UCreateSessionAsyncAction : public USessionAsyncActionBase
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Activate() override;

public:
	UFUNCTION(BlueprintCallable, Category="Generic Session", meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UCreateSessionAsyncAction* CreateSession(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, const FGenericSessionSettings& InSessionSettings);

public:
	UPROPERTY(BlueprintAssignable)
	FCreateSessionSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateSessionFail OnFail;

private:
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	void OnCreateSessionComplete(FName InSessionName, bool bWasSuccessful);
	
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;
	void OnStartSessionComplete(FName InSessionName, bool bWasSuccessful);

	UPROPERTY()
	FUniqueNetworkID UniqueNetID;

	UPROPERTY()
	FGenericSessionSettings SessionSettings;
};
