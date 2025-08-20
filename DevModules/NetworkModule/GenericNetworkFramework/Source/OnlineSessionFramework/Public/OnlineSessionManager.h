// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interface/ManagerInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OnlineSessionManager.generated.h"

class UOnlineSessionHandle;

/**
 * 
 */
UCLASS()
class ONLINESESSIONFRAMEWORK_API UOnlineSessionManager : public UGameInstanceSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	UFUNCTION(BlueprintCallable, Category = "OnlineSession", meta=(DeterminesOutputType = "InClass"))
	UOnlineSessionHandle* CreateOnlineSessionHandle(TSubclassOf<UOnlineSessionHandle> InClass);

	UFUNCTION(BlueprintCallable, Category = "OnlineSession")
	void DestroyOnlineSessionHandle(UOnlineSessionHandle* InSession);

	UFUNCTION(BlueprintPure, Category = "OnlineSession")
	UOnlineSessionHandle* FindSessionHandle(FName InSessionName);

protected:
	// virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);
	// virtual void OnStartSessionComplete(FName SessionName, bool bWasSuccessful);
	// virtual void OnUpdateSessionComplete(FName SessionName, bool bWasSuccessful);
	// virtual void OnEndSessionComplete(FName SessionName, bool bWasSuccessful);
	// virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);
	// virtual void OnMatchmakingComplete(FName SessionName, bool bWasSuccessful);
	// virtual void OnCancelMatchmakingComplete(FName SessionName, bool bWasSuccessful);
	// virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
	// virtual void OnSessionParticipantJoined(FName SessionName, const FUniqueNetId& InPlayerUniqueNetID);
	// virtual void OnSessionParticipantLeft(FName SessionName, const FUniqueNetId& InPlayerUniqueNetID, EOnSessionParticipantLeftReason LeftReason);
	// virtual void OnSessionSettingsUpdated(FName SessionName, const FOnlineSessionSettings& NewSettings);
	// virtual void OnSessionParticipantSettingsUpdated(FName SessionName, const FUniqueNetId& InPlayerUniqueNetID, const FOnlineSessionSettings& NewSettings);
	// virtual void OnRegisterPlayersComplete(FName SessionName, const TArray<FUniqueNetIdRef>& RegisteredPlayer, bool bWasSuccessful);
	// virtual void OnUnregisterPlayersComplete(FName SessionName, const TArray<FUniqueNetIdRef>& RegisteredPlayer, bool bWasSuccessful);
	// virtual void OnDestroySessionRequested(int32 PlayerNum, FName SessionName);

protected:
	UPROPERTY(Transient)
	TArray<TObjectPtr<UOnlineSessionHandle>> OnlineSessionHandles;
};
