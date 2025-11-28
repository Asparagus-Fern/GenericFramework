// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "ViewModel/SessionSearchSettingViewModel.h"

#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "ViewModel/SessionSearchResultViewModel.h"

TSharedRef<FOnlineSessionSearch> USessionSearchSettingViewModel::GetSessionSearchSettings() const
{
	return SessionSearchSettings.GetSessionSearchSettings();
}

void USessionSearchSettingViewModel::SetSessionSearchSettings(const TSharedRef<FOnlineSessionSearch>& InSessionSettings)
{
	SessionSearchSettings.SetSessionSearchSettings(InSessionSettings);
}
