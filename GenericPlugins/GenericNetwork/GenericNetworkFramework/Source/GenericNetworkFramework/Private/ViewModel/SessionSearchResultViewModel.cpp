// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "ViewModel/SessionSearchResultViewModel.h"

#include "ViewModel/SessionSettingViewModel.h"

const FOnlineSessionSearchResult& USessionSearchResultViewModel::GetSessionSearchResult()
{
	return Result;
}

void USessionSearchResultViewModel::SetSessionSearchResult(const FOnlineSessionSearchResult& InResult)
{
	Result = InResult;

	PingInMs = Result.PingInMs;
	OwnerPlayerID = Result.Session.OwningUserId;
	OwningPlayerName = Result.Session.OwningUserName;
	MaxPlayers = Result.Session.SessionSettings.NumPublicConnections + Result.Session.SessionSettings.NumPrivateConnections;
	CurrentPlayers = MaxPlayers - (Result.Session.NumOpenPublicConnections + Result.Session.NumOpenPrivateConnections);

	if (!SessionSettings)
	{
		SessionSettings = NewObject<USessionSettingViewModel>(this);
	}
	SessionSettings->SetSessionSettings(Result.Session.SessionSettings);
}

FName USessionSearchResultViewModel::GetSessionName() const
{
	if (SessionSettings)
	{
		return FName(SessionSettings->SessionName);
	}

	return NAME_None;
}
