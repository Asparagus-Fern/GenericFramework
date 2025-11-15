// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericNetworkFramework/Public/ViewModel/SessionSettingViewModel.h"

#include "OnlineSessionSettings.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameModeBase.h"
#include "Online/OnlineSessionNames.h"

const FOnlineSessionSettings& USessionSettingViewModel::GetSessionSettings()
{
	Settings.NumPublicConnections = NumPublicConnections;
	Settings.NumPrivateConnections = NumPrivateConnections;
	Settings.bShouldAdvertise = bShouldAdvertise;
	Settings.bAllowJoinInProgress = bAllowJoinInProgress;
	Settings.bIsLANMatch = bIsLANMatch;
	Settings.bIsDedicated = bIsDedicated;
	Settings.bUsesStats = bUsesStats;
	Settings.bAllowInvites = bAllowInvites;
	Settings.bUsesPresence = bUsesPresence;
	Settings.bAllowJoinViaPresence = bAllowJoinViaPresence;
	Settings.bAllowJoinViaPresenceFriendsOnly = bAllowJoinViaPresenceFriendsOnly;
	Settings.bAntiCheatProtected = bAntiCheatProtected;
	Settings.bUseLobbiesIfAvailable = bUseLobbiesIfAvailable;
	Settings.bUseLobbiesVoiceChatIfAvailable = bUseLobbiesVoiceChatIfAvailable;

	Settings.Set(SETTING_MAPNAME, MapName, EOnlineDataAdvertisementType::ViaOnlineService);
	Settings.Set(SETTING_GAMEMODE, SessionName, EOnlineDataAdvertisementType::ViaOnlineService);
	Settings.Set(SETTING_NUMBOTS, NumRobots, EOnlineDataAdvertisementType::ViaOnlineService);
	Settings.Set(SETTING_NEEDS, PlayerNeed, EOnlineDataAdvertisementType::ViaOnlineService);
	Settings.Set(SETTING_SESSIONKEY, SessionKey, EOnlineDataAdvertisementType::ViaOnlineService);

	return Settings;
}

void USessionSettingViewModel::SetSessionSettings(const FOnlineSessionSettings& InSettings)
{
	Settings = InSettings;

	NumPublicConnections = Settings.NumPublicConnections;
	NumPrivateConnections = Settings.NumPrivateConnections;
	bShouldAdvertise = Settings.bShouldAdvertise;
	bAllowJoinInProgress = Settings.bAllowJoinInProgress;
	bIsLANMatch = Settings.bIsLANMatch;
	bIsDedicated = Settings.bIsDedicated;
	bUsesStats = Settings.bUsesStats;
	bAllowInvites = Settings.bAllowInvites;
	bUsesPresence = Settings.bUsesPresence;
	bAllowJoinViaPresence = Settings.bAllowJoinViaPresence;
	bAllowJoinViaPresenceFriendsOnly = Settings.bAllowJoinViaPresenceFriendsOnly;
	bAntiCheatProtected = Settings.bAntiCheatProtected;
	bUseLobbiesIfAvailable = Settings.bUseLobbiesIfAvailable;
	bUseLobbiesVoiceChatIfAvailable = Settings.bUseLobbiesVoiceChatIfAvailable;

	Settings.Get(SETTING_MAPNAME, MapName);
	Settings.Get(SETTING_GAMEMODE, SessionName);
	Settings.Get(SETTING_NUMBOTS, NumRobots);
	Settings.Get(SETTING_NEEDS, PlayerNeed);
	Settings.Get(SETTING_SESSIONKEY, SessionKey);
}
