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
	static GENERICNETWORKFRAMEWORK_API UGenericSessionSubsystem* Get(const UObject* WorldContextObject);
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	GENERICNETWORKFRAMEWORK_API bool CreateSession(const FUniqueNetworkID& InUniqueNetID, const FGenericSessionSettings& InSessionSettings, const FOnCreateSessionCompleteDelegate& OnComplete = FOnCreateSessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool CreateSession(const FUniqueNetworkID& InUniqueNetID, FName InSessionName, const FOnlineSessionSettings& InSessionSettings, const FOnCreateSessionCompleteDelegate& OnComplete = FOnCreateSessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool StartSession(FName InSessionName, const FOnStartSessionCompleteDelegate& OnComplete = FOnStartSessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool FindSessions(const FUniqueNetworkID& InUniqueNetID, const FGenericSessionSearchSettings& InSessionSearchSettings, const FOnFindSessionsCompleteDelegate& OnComplete = FOnFindSessionsCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool FindSessions(const FUniqueNetworkID& InUniqueNetID, const TSharedRef<FOnlineSessionSearch>& InSessionSearchSettings, const FOnFindSessionsCompleteDelegate& OnComplete = FOnFindSessionsCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool FindSingleSession(const FUniqueNetworkID& InUniqueNetID, const FGenericSessionSearchResult& InResult, const FOnSingleSessionResultCompleteDelegate& OnComplete = FOnSingleSessionResultCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool FindSingleSession(const FUniqueNetworkID& InPlayerUniqueNetID, const FUniqueNetworkID& InSessionPlayerUniqueNetID, const FOnSingleSessionResultCompleteDelegate& OnComplete = FOnSingleSessionResultCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool CancelFindSessions(const FOnCancelFindSessionsCompleteDelegate& OnComplete = FOnCancelFindSessionsCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool JoinSession(const FUniqueNetworkID& InUniqueNetID, const FGenericSessionSearchResult& InResult, const FOnJoinSessionCompleteDelegate& OnComplete = FOnJoinSessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool JoinSession(const FUniqueNetworkID& InUniqueNetID, FName InSessionName, const FGenericSessionSearchResult& InResult, const FOnJoinSessionCompleteDelegate& OnComplete = FOnJoinSessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool JoinSession(const FUniqueNetworkID& InUniqueNetID, FName InSessionName, const FOnlineSessionSearchResult& InResult, const FOnJoinSessionCompleteDelegate& OnComplete = FOnJoinSessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool EndSession(FName InSessionName, const FOnEndSessionCompleteDelegate& OnComplete = FOnEndSessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool DestroySession(FName InSessionName, const FOnDestroySessionCompleteDelegate& OnComplete = FOnDestroySessionCompleteDelegate());
	GENERICNETWORKFRAMEWORK_API bool IsPlayerInSession(FName InSessionName, const FUniqueNetworkID& InUniqueNetID);

public:
	GENERICNETWORKFRAMEWORK_API bool GetSessionHandle(const FUniqueNetworkID& UniqueNetworkID, FGenericSessionHandle& OutHandle);
	GENERICNETWORKFRAMEWORK_API bool GetSessionHandle(const FUniqueNetIdRepl& UniqueNetIDRepl, FGenericSessionHandle& OutHandle);
	GENERICNETWORKFRAMEWORK_API bool GetSessionHandle(FName InSessionName, FGenericSessionHandle& OutHandle);

private:
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	void OnCreateSessionComplete(FName InSessionName, bool bWasSuccessful);

	UPROPERTY()
	TArray<FGenericSessionHandle> SessionHandles;
};
