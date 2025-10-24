// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericNetworkFramework/Public/ViewModel/OnlineSessionCreateSettingsViewModel.h"

#include "OnlineSessionSettings.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameModeBase.h"
#include "Online/OnlineSessionNames.h"

bool UOnlineSessionCreateSettingsViewModel::GetOnlineSessionCreateSettings(FOnlineSessionSettings& Result)
{
	if (const UWorld* World = GetWorld())
	{
		FOnlineSessionSettings Settings;

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
		Settings.SessionIdOverride = SessionIdOverride;

		const FString MapName = World->GetMapName();
		Settings.Set(SETTING_MAPNAME, bUseCustomMapName ? MapNameOverride : MapName, EOnlineDataAdvertisementType::ViaOnlineService);

		AGameModeBase* GameModeBase = World->GetAuthGameMode();
		if (bUseCustomGameModeDescription || (!bUseCustomGameModeDescription && GameModeBase))
		{
			Settings.Set(SETTING_GAMEMODE, bUseCustomGameModeDescription ? GameModeDescriptionOverride : GameModeBase->GetClass()->GetName(), EOnlineDataAdvertisementType::ViaOnlineService);
		}

		AGameMode* GameMode = Cast<AGameMode>(World->GetAuthGameMode());
		if (bUseCustomNumBots || (!bUseCustomNumBots && GameMode))
		{
			Settings.Set(SETTING_NUMBOTS, bUseCustomNumBots ? NumBotsOverride : GameMode->NumBots, EOnlineDataAdvertisementType::ViaOnlineService);
		}

		if (bUseNumPlayerNeeded)
		{
			Settings.Set(SETTING_NEEDS, NumPlayerNeeded, EOnlineDataAdvertisementType::ViaOnlineService);
		}

		if (bUseSessionKey && !SessionKey.IsEmpty())
		{
			Settings.Set(SETTING_SESSIONKEY, SessionKey, EOnlineDataAdvertisementType::ViaOnlineService);
		}

		Result = Settings;
		return true;
	}

	return false;
}
