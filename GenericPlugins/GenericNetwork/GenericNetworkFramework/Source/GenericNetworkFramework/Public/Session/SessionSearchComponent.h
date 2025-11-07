// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SessionSearchComponent.generated.h"

class USessionSearchPanel;
class USessionSearchSettingsViewModel;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFindSessionStart);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFindSessionSuccess);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFindSessionFail);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFindSessionCancel);

/**
 * 
 */
UCLASS(ClassGroup=(GenericFramework), meta=(BlueprintSpawnableComponent), MinimalAPI)
class USessionSearchComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USessionSearchComponent();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(BlueprintCallable)
	GENERICNETWORKFRAMEWORK_API bool FindSessionsByID(int32 HostingPlayerNum);

	UFUNCTION(BlueprintCallable)
	GENERICNETWORKFRAMEWORK_API bool FindSessionsByNetID(const FUniqueNetIdRepl& HostingPlayerId);

	UFUNCTION(BlueprintPure)
	GENERICNETWORKFRAMEWORK_API USessionSearchSettingsViewModel* GetOnlineSessionSearchSettings();

	UFUNCTION(BlueprintCallable)
	GENERICNETWORKFRAMEWORK_API void SetOnlineSessionSearchSettings(USessionSearchSettingsViewModel* InViewModel);

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
	GENERICNETWORKFRAMEWORK_API virtual void OnFindSessionsComplete(bool bWasSuccessful);
	GENERICNETWORKFRAMEWORK_API virtual void OnCancelFindSessionsComplete(bool bWasSuccessful);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USessionSearchSettingsViewModel> OnlineSessionSearchSettingsClass = nullptr;

	UPROPERTY()
	TObjectPtr<USessionSearchSettingsViewModel> OnlineSessionSearchSettings = nullptr;

private:
	TSharedPtr<class FOnlineSessionSearch> Settings;
};
