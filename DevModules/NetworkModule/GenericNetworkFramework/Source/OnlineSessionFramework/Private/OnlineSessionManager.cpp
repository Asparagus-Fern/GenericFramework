// Copyright ChenTaiye 2025. All Rights Reserved.


#include "OnlineSessionManager.h"

#include "OnlineSessionHandle.h"
#include "StaticFunctions_Online.h"


bool UOnlineSessionManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UOnlineSessionManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);

	IOnlineSessionPtr OnlineSessionPtr = FStaticFunctions_Online::GetOnlineSession();
	if (OnlineSessionPtr.IsValid())
	{
		// OnlineSessionPtr->OnCreateSessionCompleteDelegates.AddUObject(this, &UOnlineSessionManager::OnCreateSessionComplete);
		// OnlineSessionPtr->OnStartSessionCompleteDelegates.AddUObject(this, &UOnlineSessionManager::OnStartSessionComplete);
		// OnlineSessionPtr->OnUpdateSessionCompleteDelegates.AddUObject(this, &UOnlineSessionManager::OnUpdateSessionComplete);
		// OnlineSessionPtr->OnEndSessionCompleteDelegates.AddUObject(this, &UOnlineSessionManager::OnEndSessionComplete);
		// OnlineSessionPtr->OnDestroySessionCompleteDelegates.AddUObject(this, &UOnlineSessionManager::OnDestroySessionComplete);
		// OnlineSessionPtr->OnMatchmakingCompleteDelegates.AddUObject(this, &UOnlineSessionManager::OnMatchmakingComplete);
		// OnlineSessionPtr->OnCancelMatchmakingCompleteDelegates.AddUObject(this, &UOnlineSessionManager::OnCancelMatchmakingComplete);
		// OnlineSessionPtr->OnJoinSessionCompleteDelegates.AddUObject(this, &UOnlineSessionManager::OnJoinSessionComplete);
		// OnlineSessionPtr->OnSessionParticipantJoinedDelegates.AddUObject(this, &UOnlineSessionManager::OnSessionParticipantJoined);
		// OnlineSessionPtr->OnSessionParticipantLeftDelegates.AddUObject(this, &UOnlineSessionManager::OnSessionParticipantLeft);
		// OnlineSessionPtr->OnSessionSettingsUpdatedDelegates.AddUObject(this, &UOnlineSessionManager::OnSessionSettingsUpdated);
		// OnlineSessionPtr->OnSessionParticipantSettingsUpdatedDelegates.AddUObject(this, &UOnlineSessionManager::OnSessionParticipantSettingsUpdated);
		// OnlineSessionPtr->OnRegisterPlayersCompleteDelegates.AddUObject(this, &UOnlineSessionManager::OnRegisterPlayersComplete);
		// OnlineSessionPtr->OnUnregisterPlayersCompleteDelegates.AddUObject(this, &UOnlineSessionManager::OnUnregisterPlayersComplete);
		// OnlineSessionPtr->OnDestroySessionRequestedDelegates.AddUObject(this, &UOnlineSessionManager::OnDestroySessionRequested);
	}
}

void UOnlineSessionManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

UOnlineSessionHandle* UOnlineSessionManager::CreateOnlineSessionHandle(TSubclassOf<UOnlineSessionHandle> InClass)
{
	ensure(InClass);

	UOnlineSessionHandle* NewOnlineSessionHandle = NewObject<UOnlineSessionHandle>(this, InClass);
	NewOnlineSessionHandle->NativeOnCreate();
	OnlineSessionHandles.Add(NewOnlineSessionHandle);

	return Cast<UOnlineSessionHandle>(NewOnlineSessionHandle);
}

void UOnlineSessionManager::DestroyOnlineSessionHandle(UOnlineSessionHandle* InSession)
{
	if (OnlineSessionHandles.Contains(InSession))
	{
		OnlineSessionHandles.Remove(InSession);
		InSession->NativeOnDestroy();
	}
}

UOnlineSessionHandle* UOnlineSessionManager::FindSessionHandle(FName InSessionName)
{
	// for (auto& OnlineSessionHandle : OnlineSessionHandles)
	// {
	// 	if (OnlineSessionHandle->GetSessionName() == InSessionName)
	// 	{
	// 		return OnlineSessionHandle;
	// 	}
	// }

	return nullptr;
}

