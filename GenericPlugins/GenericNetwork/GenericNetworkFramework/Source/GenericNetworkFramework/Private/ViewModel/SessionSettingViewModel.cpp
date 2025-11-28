// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericNetworkFramework/Public/ViewModel/SessionSettingViewModel.h"

#include "OnlineSessionSettings.h"
#include "GameFramework/GameMode.h"
#include "GameFramework/GameModeBase.h"
#include "Online/OnlineSessionNames.h"

const FOnlineSessionSettings& USessionSettingViewModel::GetSessionSettings() const
{
	return SessionSettings.GetSessionSettings();
}

void USessionSettingViewModel::SetSessionSettings(const FOnlineSessionSettings& InSettings)
{
	SessionSettings.SetSessionSettings(InSettings);
}
