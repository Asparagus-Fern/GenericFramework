// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "NetworkType.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystem/GenericGameInstanceSubsystem.h"
#include "GenericSessionSubsystem.generated.h"

class USessionSearchSettingViewModel;
class USessionSettingViewModel;

/**
 * 
 */
UCLASS(MinimalAPI)
class UGenericSessionSubsystem : public UGenericGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	static UGenericSessionSubsystem* Get(const UObject* WorldContextObject);
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	GENERICNETWORKFRAMEWORK_API bool CreateSession(const FUniqueNetworkID& InUniqueNetID, FName InSessionName, TSubclassOf<USessionSettingViewModel> InViewModelClass, const FOnCreateSessionCompleteDelegate& OnComplete = FOnCreateSessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool CreateSession(const FUniqueNetworkID& InUniqueNetID, FName InSessionName, USessionSettingViewModel* InViewModel, const FOnCreateSessionCompleteDelegate& OnComplete = FOnCreateSessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool CreateSession(const FUniqueNetworkID& InUniqueNetID, FName InSessionName, const FOnlineSessionSettings& InSessionSettings, const FOnCreateSessionCompleteDelegate& OnComplete = FOnCreateSessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool StartSession(FName InSessionName, const FOnStartSessionCompleteDelegate& OnComplete = FOnStartSessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool FindSessions(const FUniqueNetworkID& InUniqueNetID, TSubclassOf<USessionSearchSettingViewModel> InViewModelClass, const FOnFindSessionsCompleteDelegate& OnComplete = FOnFindSessionsCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool FindSessions(const FUniqueNetworkID& InUniqueNetID, USessionSearchSettingViewModel* InViewModel, const FOnFindSessionsCompleteDelegate& OnComplete = FOnFindSessionsCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool FindSessions(const FUniqueNetworkID& InUniqueNetID, const TSharedRef<FOnlineSessionSearch>& InSearchSettings, const FOnFindSessionsCompleteDelegate& OnComplete = FOnFindSessionsCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool CancelFindSessions(const FOnCancelFindSessionsCompleteDelegate& OnComplete = FOnCancelFindSessionsCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool JoinSession(const FUniqueNetworkID& InUniqueNetID, FName InSessionName, const FOnlineSessionSearchResult& DesiredSession, const FOnJoinSessionCompleteDelegate& OnComplete = FOnJoinSessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool EndSession(FName InSessionName, const FOnEndSessionCompleteDelegate& OnComplete = FOnEndSessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool DestroySession(FName InSessionName, const FOnDestroySessionCompleteDelegate& OnComplete = FOnDestroySessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool IsPlayerInSession(FName InSessionName, const FUniqueNetworkID& InUniqueNetID);

private:
	UPROPERTY()
	TArray<TObjectPtr<USessionSettingViewModel>> SessionSettingViewModels;
	
	UPROPERTY()
	TArray<TObjectPtr<USessionSearchSettingViewModel>> SessionSearchSettingViewModels;
};
