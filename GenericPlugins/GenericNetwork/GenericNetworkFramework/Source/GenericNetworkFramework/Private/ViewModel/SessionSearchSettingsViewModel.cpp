// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericNetworkFramework/Public/ViewModel/SessionSearchSettingsViewModel.h"

#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"


/*bool USessionSearchSettingsViewModel::GetOnlineSessionSearchSettings(TSharedPtr<FOnlineSessionSearch>& Result)
{
	TSharedRef<FOnlineSessionSearch> Settings = MakeShareable(new FOnlineSessionSearch());

	Settings->MaxSearchResults = MaxSearchResults;
	Settings->bIsLanQuery = bIsLanQuery;
	Settings->TimeoutInSeconds = TimeoutInSeconds;

	Settings->QuerySettings.Set(SEARCH_DEDICATED_ONLY, bDedicatedOnly, EOnlineComparisonOp::Equals);
	Settings->QuerySettings.Set(SEARCH_EMPTY_SERVERS_ONLY, bEmptyServerOnly, EOnlineComparisonOp::Equals);
	Settings->QuerySettings.Set(SEARCH_NONEMPTY_SERVERS_ONLY, bNotEmptyServerOnly, EOnlineComparisonOp::Equals);

	if (!SearchUserName.IsEmpty())
	{
		Settings->QuerySettings.Set(SEARCH_USER, SearchUserName, EOnlineComparisonOp::Equals);
	}

	if (!SearchKeywords.IsEmpty())
	{
		Settings->QuerySettings.Set(SEARCH_KEYWORDS, SearchKeywords, EOnlineComparisonOp::In);
	}

	Result = Settings;
	return true;
}*/
