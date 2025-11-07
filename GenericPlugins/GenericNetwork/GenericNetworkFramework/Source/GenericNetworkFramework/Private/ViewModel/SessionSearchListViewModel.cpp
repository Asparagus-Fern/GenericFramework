// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "ViewModel/SessionSearchListViewModel.h"

int32 USessionSearchListViewModel::GetItemsPerPage() const
{
	return ItemsPerPage;
}

void USessionSearchListViewModel::SetItemsPerPage(int32 InValue)
{
	if (UE_MVVM_SET_PROPERTY_VALUE_INLINE(ItemsPerPage, InValue))
	{
		SetTotalPageIndex((SearchResults.Num() - 1) / ItemsPerPage);
		OnGetPageSessionSearchResultEvent.Broadcast(GetPageResult());
	}
}

int32 USessionSearchListViewModel::GetPageIndex() const
{
	return PageIndex;
}

void USessionSearchListViewModel::SetPageIndex(int32 InValue)
{
	if (InValue < 0 || InValue > TotalPageIndex)
	{
		//InValid Index
		return;
	}

	if (UE_MVVM_SET_PROPERTY_VALUE_INLINE(PageIndex, InValue))
	{
		OnGetPageSessionSearchResultEvent.Broadcast(GetPageResult());
	}
}

int32 USessionSearchListViewModel::GetTotalPageIndex() const
{
	return TotalPageIndex;
}

void USessionSearchListViewModel::SetTotalPageIndex(int32 InValue)
{
	if (InValue < 0)
	{
		UE_MVVM_SET_PROPERTY_VALUE_INLINE(TotalPageIndex, 0);
	}
	else
	{
		UE_MVVM_SET_PROPERTY_VALUE_INLINE(TotalPageIndex, InValue);
	}
}

const TArray<FOnlineSessionSearchResult>& USessionSearchListViewModel::GetSearchResults()
{
	return SearchResults;
}

void USessionSearchListViewModel::SetSearchResults(const TArray<FOnlineSessionSearchResult>& InResults)
{
	SearchResults = InResults;
	OnGetSessionSearchResultEvent.Broadcast(SearchResults);
}

TArray<FOnlineSessionSearchResult> USessionSearchListViewModel::GetPageResult()
{
	TArray<FOnlineSessionSearchResult> Results;

	for (int i = PageIndex * ItemsPerPage; i < SearchResults.Num(); ++i)
	{
		Results.Add(SearchResults[i]);

		if (Results.Num() == ItemsPerPage)
		{
			break;
		}
	}

	return Results;
}
