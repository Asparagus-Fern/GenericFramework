// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "NetworkType.h"
#include "SessionAsyncActionBase.h"
#include "FindSessionAsyncAction.generated.h"

class USessionSearchSettingViewModel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFindSessionSuccess, USessionSearchSettingViewModel*, SearchSettingViewModel);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FFindSessionFail);

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API UFindSessionAsyncAction : public USessionAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

public:
	UFUNCTION(BlueprintCallable, Category="Generic Session", meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UFindSessionAsyncAction* FindSessionsByClass(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, TSubclassOf<USessionSearchSettingViewModel> InViewModelClass);

	UFUNCTION(BlueprintCallable, Category="Generic Session", meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UFindSessionAsyncAction* FindSessions(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, USessionSearchSettingViewModel* InViewModel);

public:
	UPROPERTY(BlueprintAssignable)
	FFindSessionSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FFindSessionFail OnFail;

private:
	void OnFindSessionComplete(bool bWasSuccessful);

	UPROPERTY()
	FUniqueNetworkID UniqueNetID;

	UPROPERTY()
	TSubclassOf<USessionSearchSettingViewModel> ViewModelClass = nullptr;

	UPROPERTY()
	TObjectPtr<USessionSearchSettingViewModel> ViewModel = nullptr;
};
