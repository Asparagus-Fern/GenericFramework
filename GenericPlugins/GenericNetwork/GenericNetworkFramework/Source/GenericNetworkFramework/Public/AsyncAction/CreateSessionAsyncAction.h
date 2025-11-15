// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "NetworkType.h"
#include "SessionAsyncActionBase.h"
#include "CreateSessionAsyncAction.generated.h"

class USessionSettingViewModel;
class UCreateSessionHandle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreateSessionSuccess, USessionSettingViewModel*, SessionSettingViewModel);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCreateSessionFail);

/**
 * 
 */
UCLASS()
class GENERICNETWORKFRAMEWORK_API UCreateSessionAsyncAction : public USessionAsyncActionBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

public:
	UFUNCTION(BlueprintCallable, Category="Generic Session", meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UCreateSessionAsyncAction* CreateSessionByClass(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, FName InSessionName, TSubclassOf<USessionSettingViewModel> InViewModelClass, bool IsAutoStart = true);

	UFUNCTION(BlueprintCallable, Category="Generic Session", meta = (WorldContext = "InWorldContextObject", BlueprintInternalUseOnly = "true"))
	static UCreateSessionAsyncAction* CreateSession(UObject* InWorldContextObject, const FUniqueNetworkID& InPlayerNetID, FName InSessionName, USessionSettingViewModel* InViewModel, bool IsAutoStart = true);

public:
	UPROPERTY(BlueprintAssignable)
	FCreateSessionSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateSessionFail OnFail;

private:
	void OnCreateSessionComplete(FName InSessionName, bool bWasSuccessful);
	void OnStartSessionComplete(FName InSessionName, bool bWasSuccessful);

	UPROPERTY()
	FUniqueNetworkID UniqueNetID;

	UPROPERTY()
	FName SessionName = NAME_None;

	UPROPERTY()
	TSubclassOf<USessionSettingViewModel> ViewModelClass = nullptr;

	UPROPERTY()
	TObjectPtr<USessionSettingViewModel> ViewModel = nullptr;

	UPROPERTY()
	bool bIsAutoStart = false;
};
