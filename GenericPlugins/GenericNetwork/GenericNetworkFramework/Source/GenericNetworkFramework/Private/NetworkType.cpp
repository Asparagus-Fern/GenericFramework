// Copyright ChenTaiye 2025. All Rights Reserved.

#include "NetworkType.h"

#include "BPFunctions/BPFunctions_Device.h"
#include "GameFramework/PlayerState.h"
#include "Online/OnlineSessionNames.h"

DEFINE_LOG_CATEGORY(GenericLogNetwork);

/* ==================== FUniqueNetworkID ==================== */

FUniqueNetworkID::FUniqueNetworkID()
{
	UniqueID = UBPFunctions_Device::GetDeviceID();
}

FUniqueNetworkID::FUniqueNetworkID(const APlayerController* InPlayer)
{
	UniqueID = UBPFunctions_Device::GetDeviceID();

	if (IsValid(InPlayer))
	{
		if (APlayerState* PlayerState = InPlayer->GetPlayerState<APlayerState>())
		{
			UniqueNetIdRepl = PlayerState->GetUniqueId();
		}
	}
}

FUniqueNetworkID::FUniqueNetworkID(const APlayerState* InPlayerState)
{
	UniqueID = UBPFunctions_Device::GetDeviceID();

	if (IsValid(InPlayerState))
	{
		UniqueNetIdRepl = InPlayerState->GetUniqueId();
		UniqueNetIdRepl.GetUniqueNetId();
	}
}

FUniqueNetworkID::FUniqueNetworkID(const FUniqueNetIdRepl& InUniqueNetIDRepl)
{
	UniqueID = UBPFunctions_Device::GetDeviceID();
	UniqueNetIdRepl = InUniqueNetIDRepl;
}

/* ==================== FGenericSessionSettings ==================== */

FGenericSessionSettings::FGenericSessionSettings()
	: SessionName(LexToString(NAME_GameSession))
{
}

FGenericSessionSettings::FGenericSessionSettings(const FOnlineSessionSettings& InSettings)
	: SessionName(LexToString(NAME_GameSession))
{
	SetSessionSettings(InSettings);
}

const FOnlineSessionSettings& FGenericSessionSettings::GetSessionSettings() const
{
	return SessionSettings;
}

void FGenericSessionSettings::SetSessionSettings(const FOnlineSessionSettings& InSettings)
{
	SessionSettings = InSettings;
	DecodeSessionSettings();
}

void FGenericSessionSettings::EncodeSessionSettings()
{
	SessionSettings.NumPublicConnections = NumPublicConnections;
	SessionSettings.NumPrivateConnections = NumPrivateConnections;
	SessionSettings.bShouldAdvertise = bShouldAdvertise;
	SessionSettings.bAllowJoinInProgress = bAllowJoinInProgress;
	SessionSettings.bIsLANMatch = bIsLANMatch;
	SessionSettings.bIsDedicated = bIsDedicated;
	SessionSettings.bUsesStats = bUsesStats;
	SessionSettings.bAllowInvites = bAllowInvites;
	SessionSettings.bUsesPresence = bUsesPresence;
	SessionSettings.bAllowJoinViaPresence = bAllowJoinViaPresence;
	SessionSettings.bAllowJoinViaPresenceFriendsOnly = bAllowJoinViaPresenceFriendsOnly;
	SessionSettings.bAntiCheatProtected = bAntiCheatProtected;
	SessionSettings.bUseLobbiesIfAvailable = bUseLobbiesIfAvailable;
	SessionSettings.bUseLobbiesVoiceChatIfAvailable = bUseLobbiesVoiceChatIfAvailable;

	SessionSettings.Set(SETTING_MAPNAME, MapName, EOnlineDataAdvertisementType::ViaOnlineService);
	SessionSettings.Set(SETTING_GAMEMODE, SessionName, EOnlineDataAdvertisementType::ViaOnlineService);
	SessionSettings.Set(SETTING_NUMBOTS, NumRobots, EOnlineDataAdvertisementType::ViaOnlineService);
	SessionSettings.Set(SETTING_NEEDS, PlayerNeed, EOnlineDataAdvertisementType::ViaOnlineService);
	SessionSettings.Set(SETTING_SESSIONKEY, SessionKey, EOnlineDataAdvertisementType::ViaOnlineService);
}

void FGenericSessionSettings::DecodeSessionSettings()
{
	NumPublicConnections = SessionSettings.NumPublicConnections;
	NumPrivateConnections = SessionSettings.NumPrivateConnections;
	bShouldAdvertise = SessionSettings.bShouldAdvertise;
	bAllowJoinInProgress = SessionSettings.bAllowJoinInProgress;
	bIsLANMatch = SessionSettings.bIsLANMatch;
	bIsDedicated = SessionSettings.bIsDedicated;
	bUsesStats = SessionSettings.bUsesStats;
	bAllowInvites = SessionSettings.bAllowInvites;
	bUsesPresence = SessionSettings.bUsesPresence;
	bAllowJoinViaPresence = SessionSettings.bAllowJoinViaPresence;
	bAllowJoinViaPresenceFriendsOnly = SessionSettings.bAllowJoinViaPresenceFriendsOnly;
	bAntiCheatProtected = SessionSettings.bAntiCheatProtected;
	bUseLobbiesIfAvailable = SessionSettings.bUseLobbiesIfAvailable;
	bUseLobbiesVoiceChatIfAvailable = SessionSettings.bUseLobbiesVoiceChatIfAvailable;

	SessionSettings.Get(SETTING_MAPNAME, MapName);
	SessionSettings.Get(SETTING_GAMEMODE, SessionName);
	SessionSettings.Get(SETTING_NUMBOTS, NumRobots);
	SessionSettings.Get(SETTING_NEEDS, PlayerNeed);
	SessionSettings.Get(SETTING_SESSIONKEY, SessionKey);
}

/* ==================== FGenericSessionSearchSettings ==================== */

FGenericSessionSearchSettings::FGenericSessionSearchSettings()
{
	if (!SessionSearchSettings.IsValid())
	{
		SessionSearchSettings = MakeShareable(new FOnlineSessionSearch());
	}
}

FGenericSessionSearchSettings::FGenericSessionSearchSettings(const TSharedRef<FOnlineSessionSearch>& InSettings)
{
	if (!SessionSearchSettings.IsValid())
	{
		SessionSearchSettings = MakeShareable(new FOnlineSessionSearch());
	}

	SetSessionSearchSettings(InSettings);
}

TSharedRef<FOnlineSessionSearch> FGenericSessionSearchSettings::GetSessionSearchSettings() const
{
	return SessionSearchSettings.ToSharedRef();
}

void FGenericSessionSearchSettings::SetSessionSearchSettings(const TSharedRef<FOnlineSessionSearch>& InSettings)
{
	SessionSearchSettings = InSettings;
	DecodeSessionSearchSettings();
}

void FGenericSessionSearchSettings::EncodeSessionSearchSettings()
{
	SessionSearchSettings->MaxSearchResults = MaxSearchResults;
	SessionSearchSettings->bIsLanQuery = bIsLanQuery;
	SessionSearchSettings->TimeoutInSeconds = TimeoutInSeconds;

	SessionSearchSettings->QuerySettings.Set(SEARCH_DEDICATED_ONLY, bDedicatedOnly, EOnlineComparisonOp::Equals);
	SessionSearchSettings->QuerySettings.Set(SEARCH_EMPTY_SERVERS_ONLY, bEmptyServerOnly, EOnlineComparisonOp::Equals);
	SessionSearchSettings->QuerySettings.Set(SEARCH_NONEMPTY_SERVERS_ONLY, bNotEmptyServerOnly, EOnlineComparisonOp::Equals);
	SessionSearchSettings->QuerySettings.Set(SEARCH_USER, SearchUserName, EOnlineComparisonOp::In);
	SessionSearchSettings->QuerySettings.Set(SEARCH_KEYWORDS, SearchKeywords, EOnlineComparisonOp::In);
}

void FGenericSessionSearchSettings::DecodeSessionSearchSettings()
{
	MaxSearchResults = SessionSearchSettings->MaxSearchResults;
	bIsLanQuery = SessionSearchSettings->bIsLanQuery;
	TimeoutInSeconds = SessionSearchSettings->TimeoutInSeconds;

	SessionSearchSettings->QuerySettings.Get(SEARCH_DEDICATED_ONLY, bDedicatedOnly);
	SessionSearchSettings->QuerySettings.Get(SEARCH_EMPTY_SERVERS_ONLY, bEmptyServerOnly);
	SessionSearchSettings->QuerySettings.Get(SEARCH_NONEMPTY_SERVERS_ONLY, bNotEmptyServerOnly);
	SessionSearchSettings->QuerySettings.Get(SEARCH_USER, SearchUserName);
	SessionSearchSettings->QuerySettings.Get(SEARCH_KEYWORDS, SearchKeywords);
}

/* ==================== FGenericSessionSearchResult ==================== */

FGenericSessionSearchResult::FGenericSessionSearchResult()
{
}

FGenericSessionSearchResult::FGenericSessionSearchResult(const FOnlineSessionSearchResult& InResult)
{
	SetSessionSearchResult(InResult);
}

const FOnlineSessionSearchResult& FGenericSessionSearchResult::GetSessionSearchResult() const
{
	return SessionSearchResult;
}

void FGenericSessionSearchResult::SetSessionSearchResult(const FOnlineSessionSearchResult& InResult)
{
	SessionSearchResult = InResult;

	PingInMs = InResult.PingInMs;
	OwnerPlayerID = InResult.Session.OwningUserId;
	OwningPlayerName = InResult.Session.OwningUserName;

	MaxPlayers = InResult.Session.SessionSettings.NumPublicConnections + InResult.Session.SessionSettings.NumPrivateConnections;
	CurrentPlayers = MaxPlayers - (InResult.Session.NumOpenPublicConnections + InResult.Session.NumOpenPrivateConnections);

	SessionSettings = InResult.Session.SessionSettings;
}

FName FGenericSessionSearchResult::GetSessionName() const
{
	return FName(SessionSettings.SessionName);
}
