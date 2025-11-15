// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NetworkType.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "JoinSessionAsyncAction.generated.h"

class USessionSearchResultViewModel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FJoinSessionComplete, EJoinSessionResult, Result);

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API UJoinSessionAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

public:
	UFUNCTION(BlueprintCallable, Category="Generic Session", meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UJoinSessionAsyncAction* JoinSession(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, USessionSearchResultViewModel* InViewModel);

public:
	UPROPERTY(BlueprintAssignable)
	FJoinSessionComplete OnComplete;

private:
	void OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type Result);

	UPROPERTY()
	UObject* WorldContextObject = nullptr;

	UPROPERTY()
	FUniqueNetworkID UniqueNetID;

	UPROPERTY()
	TObjectPtr<USessionSearchResultViewModel> ViewModel;
};
