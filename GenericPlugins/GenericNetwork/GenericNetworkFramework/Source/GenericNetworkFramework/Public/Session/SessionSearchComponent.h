// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SessionSearchComponent.generated.h"

class USessionSearchPanel;
class UOnlineSessionSearchSettingsViewModel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFindSessionStart);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFindSessionSuccess);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFindSessionFail);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFindSessionCancel);

/**
 * 
 */
UCLASS(ClassGroup=(Developer), meta=(BlueprintSpawnableComponent), MinimalAPI)
class USessionSearchComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USessionSearchComponent();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(BlueprintCallable)
	void OpenSessionSearchPanel();

	UFUNCTION(BlueprintCallable)
	void CloseSessionSearchPanel();

	UFUNCTION(BlueprintCallable)
	GENERICNETWORKFRAMEWORK_API bool FindSessionsByID(int32 HostingPlayerNum, UOnlineSessionSearchSettingsViewModel* InSettings = nullptr);

	UFUNCTION(BlueprintCallable)
	GENERICNETWORKFRAMEWORK_API bool FindSessionsByNetID(const FUniqueNetIdRepl& HostingPlayerId, UOnlineSessionSearchSettingsViewModel* InSettings = nullptr);

public:
	UPROPERTY(BlueprintAssignable)
	FOnFindSessionStart OnFindSessionStart;

	UPROPERTY(BlueprintAssignable)
	FOnFindSessionSuccess OnFindSessionSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnFindSessionFail OnFindSessionFail;

	UPROPERTY(BlueprintAssignable)
	FOnFindSessionCancel OnFindSessionCancel;

protected:
	GENERICNETWORKFRAMEWORK_API virtual void FindSessionsInternal();
	GENERICNETWORKFRAMEWORK_API virtual void OnFindSessionsComplete(bool bWasSuccessful);
	GENERICNETWORKFRAMEWORK_API virtual void OnCancelFindSessionsComplete(bool bWasSuccessful);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USessionSearchPanel> SessionSearchPanelClass = nullptr;

	UPROPERTY()
	TObjectPtr<USessionSearchPanel> SessionSearchPanel = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UOnlineSessionSearchSettingsViewModel> OnlineSessionSearchSettingsClass = nullptr;

	UPROPERTY()
	TObjectPtr<UOnlineSessionSearchSettingsViewModel> OnlineSessionSearchSettings = nullptr;

private:
	TSharedPtr<class FOnlineSessionSearch> Settings;
};
