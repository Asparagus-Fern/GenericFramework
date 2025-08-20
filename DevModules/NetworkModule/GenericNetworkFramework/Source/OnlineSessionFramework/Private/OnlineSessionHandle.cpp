// Copyright ChenTaiye 2025. All Rights Reserved.

#include "OnlineSessionHandle.h"

#include "OnlineSubsystem.h"
#include "StaticFunctions_Online.h"
#include "BPFunctions/BPFunctions_Gameplay.h"
#include "MVVM/SessionSettingViewModel.h"

void UOnlineSessionHandle::NativeOnCreate()
{
	IStateInterface::NativeOnCreate();

	if (!SessionSettingViewModel)
	{
		SessionSettingViewModel = NewObject<USessionSettingViewModel>();
	}

	IOnlineSessionPtr OnlineSessionPtr = FStaticFunctions_Online::GetOnlineSession();
	if (OnlineSessionPtr.IsValid())
	{
		// OnlineSessionPtr->OnFindSessionsCompleteDelegates.AddUObject(this, &UOnlineSessionHandle::OnFindSessionsComplete);
		// OnlineSessionPtr->OnCancelFindSessionsCompleteDelegates.AddUObject(this, &UOnlineSessionHandle::OnCancelFindSessionsComplete);
		// OnlineSessionPtr->OnPingSearchResultsCompleteDelegates.AddUObject(this, &UOnlineSessionHandle::OnPingSearchResultsComplete);
		// OnlineSessionPtr->OnFindFriendSessionCompleteDelegates->AddUObject(this, &UOnlineSessionHandle::OnFindFriendSessionComplete);
		// OnlineSessionPtr->OnSessionInviteReceivedDelegates.AddUObject(this, &UOnlineSessionHandle::OnSessionInviteReceived);
		// OnlineSessionPtr->OnSessionUserInviteAcceptedDelegates.AddUObject(this, &UOnlineSessionHandle::OnSessionInviteAccepted);
		// OnlineSessionPtr->OnSessionFailureDelegates.AddUObject(this, &UOnlineSessionHandle::OnSessionFailure);
	}
}

void UOnlineSessionHandle::NativeOnDestroy()
{
	IStateInterface::NativeOnDestroy();
}

void UOnlineSessionHandle::CreateSessionByPlayerIndex(int32 InPlayerIndex)
{
	IOnlineSessionPtr OnlineSessionPtr = FStaticFunctions_Online::GetOnlineSession();
	if (OnlineSessionPtr.IsValid())
	{
	}
}

void UOnlineSessionHandle::CreateSessionByPlayerUniqueNetID(const FUniqueNetIdRepl& InPlayerNetID)
{
}

/*
bool UOnlineSessionHandle::CreateOnlineSession(int32 InPlayerIndex, FName SessionName, const FOnlineSessionSettings& SessionSettings)
{
	IOnlineSessionPtr OnlineSessionPtr = FStaticFunctions_Online::GetOnlineSession();
	if (OnlineSessionPtr.IsValid())
	{
		OnlineSessionPtr->OnCreateSessionCompleteDelegates.AddUObject()
		return OnlineSessionPtr->CreateSession(InPlayerIndex, SessionName, SessionSettings);
	}

	return false;
}

bool UOnlineSessionHandle::CreateOnlineSession(APlayerController* InPlayer, FName SessionName, const FOnlineSessionSettings& SessionSettings)
{
	if (!IsValid(InPlayer))
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("InPlayer Is InValid"))
		return false;
	}

	const FUniqueNetIdRepl& UniqueNetIdRepl = UBPFunctions_Gameplay::GetPlayerUniqueNetID(InPlayer);
	if (!UniqueNetIdRepl.GetUniqueNetId().IsValid())
	{
		GenericLOG(GenericLogNetwork, Error, TEXT("Player UniqueNetId Is InValid"))
		return false;
	}

	IOnlineSessionPtr OnlineSessionPtr = FStaticFunctions_Online::GetOnlineSession();
	if (OnlineSessionPtr.IsValid())
	{
		const FUniqueNetId* UniqueNetId = UniqueNetIdRepl.GetUniqueNetId().Get();
		return OnlineSessionPtr->CreateSession(*UniqueNetId, SessionName, SessionSettings);
	}

	return false;
}
*/
