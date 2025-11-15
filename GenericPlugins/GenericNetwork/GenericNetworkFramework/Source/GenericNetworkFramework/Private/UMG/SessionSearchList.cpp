// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "UMG/SessionSearchList.h"

#include "Components/ListView.h"
#include "UMG/SessionSearchListItem.h"
#include "ViewModel/SessionSearchResultViewModel.h"

void USessionSearchList::NativeConstruct()
{
	Super::NativeConstruct();
}

void USessionSearchList::NativeDestruct()
{
	Super::NativeDestruct();
}

void USessionSearchList::SetSessionSearchResult(const TArray<USessionSearchResultViewModel*>& InViewModels)
{
	if (ListView_SessionSearch)
	{
		ListView_SessionSearch->ClearListItems();
		SessionSearchListItemObjects.Reset();

		for (auto& ViewModel : InViewModels)
		{
			USessionSearchListItemObject* NewItemObject = NewObject<USessionSearchListItemObject>(this);
			NewItemObject->SessionSearchResultViewModel = ViewModel;
			SessionSearchListItemObjects.Add(NewItemObject);
			ListView_SessionSearch->AddItem(NewItemObject);
		}
	}
}

void USessionSearchList::OnFindSessionsStart_Implementation()
{
}

void USessionSearchList::OnFindSessionsComplete_Implementation()
{
}
