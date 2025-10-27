// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "UMG/SessionSearchPanel.h"

#include "WidgetType.h"
#include "ViewModel/OnlineSessionSearchSettingsViewModel.h"

UOnlineSessionSearchSettingsViewModel* USessionSearchPanel::GetSessionSearchSettingsViewModel()
{
	return OnlineSessionSearchSettingsViewModel;
}

void USessionSearchPanel::SetOnlineSessionSearchSettingsViewModel(UOnlineSessionSearchSettingsViewModel* InViewModel)
{
	UNREGISTER_MVVM_PROPERTY(OnlineSessionSearchSettingsViewModel);

	OnlineSessionSearchSettingsViewModel = InViewModel;

	if (OnlineSessionSearchSettingsViewModel)
	{
		
	}
}
