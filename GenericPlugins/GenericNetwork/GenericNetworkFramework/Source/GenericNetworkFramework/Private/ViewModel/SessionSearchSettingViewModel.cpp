// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "ViewModel/SessionSearchSettingViewModel.h"

#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "ViewModel/SessionSearchResultViewModel.h"

TSharedRef<FOnlineSessionSearch> USessionSearchSettingViewModel::GetSessionSettings()
{
	if (!SessionSettings.IsValid())
	{
		SessionSettings = MakeShareable(new FOnlineSessionSearch());
	}

	SessionSettings->MaxSearchResults = MaxSearchResults;
	SessionSettings->bIsLanQuery = bIsLanQuery;
	SessionSettings->TimeoutInSeconds = TimeoutInSeconds;

	SessionSettings->QuerySettings.Set(SEARCH_DEDICATED_ONLY, bDedicatedOnly, EOnlineComparisonOp::Equals);
	SessionSettings->QuerySettings.Set(SEARCH_EMPTY_SERVERS_ONLY, bEmptyServerOnly, EOnlineComparisonOp::Equals);
	SessionSettings->QuerySettings.Set(SEARCH_NONEMPTY_SERVERS_ONLY, bNotEmptyServerOnly, EOnlineComparisonOp::Equals);

	if (!SearchUserName.IsEmpty())
	{
		SessionSettings->QuerySettings.Set(SEARCH_USER, SearchUserName, EOnlineComparisonOp::Equals);
	}

	if (!SearchKeywords.IsEmpty())
	{
		SessionSettings->QuerySettings.Set(SEARCH_KEYWORDS, SearchKeywords, EOnlineComparisonOp::In);
	}

	return SessionSettings.ToSharedRef();
}

void USessionSearchSettingViewModel::SetSessionSettings(const TSharedRef<FOnlineSessionSearch>& InSessionSettings)
{
	SessionSettings = InSessionSettings;

	MaxSearchResults = SessionSettings->MaxSearchResults;
	bIsLanQuery = SessionSettings->bIsLanQuery;
	TimeoutInSeconds = SessionSettings->TimeoutInSeconds;

	SessionSettings->QuerySettings.Get(SEARCH_DEDICATED_ONLY, bDedicatedOnly);
	SessionSettings->QuerySettings.Get(SEARCH_EMPTY_SERVERS_ONLY, bEmptyServerOnly);
	SessionSettings->QuerySettings.Get(SEARCH_NONEMPTY_SERVERS_ONLY, bNotEmptyServerOnly);
	SessionSettings->QuerySettings.Get(SEARCH_USER, SearchUserName);
	SessionSettings->QuerySettings.Get(SEARCH_KEYWORDS, SearchKeywords);
}

void USessionSearchSettingViewModel::GetSessionSearchResults(TArray<USessionSearchResultViewModel*>& OutResults) const
{
	OutResults = SearchResults;
}

void USessionSearchSettingViewModel::RefreshSessionSearchResults()
{
	SearchResults.Reset();

	for (auto& SearchResult : SessionSettings->SearchResults)
	{
		USessionSearchResultViewModel* NewViewModel = NewObject<USessionSearchResultViewModel>(this);
		NewViewModel->SetSessionSearchResult(SearchResult);
		SearchResults.Add(NewViewModel);
	}
}
