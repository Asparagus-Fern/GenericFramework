// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "ViewModel/SessionSearchResultViewModel.h"

const FOnlineSessionSearchResult& USessionSearchResultViewModel::GetSessionSearchResult() const
{
	return SessionSearchResult.GetSessionSearchResult();
}

void USessionSearchResultViewModel::SetSessionSearchResult(const FOnlineSessionSearchResult& InResult)
{
	SessionSearchResult.SetSessionSearchResult(InResult);
}
