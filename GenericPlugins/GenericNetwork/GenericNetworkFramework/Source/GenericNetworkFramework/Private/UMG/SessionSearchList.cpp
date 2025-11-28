// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "UMG/SessionSearchList.h"

#include "Components/ListView.h"
#include "UMG/SessionSearchListItem.h"
#include "UMG/SessionSettingPanel.h"
#include "ViewModel/SessionSearchResultViewModel.h"

void USessionSearchList::NativeConstruct()
{
	Super::NativeConstruct();

	if (ListView_SessionSearch)
	{
		ListView_SessionSearch->OnItemSelectionChanged().AddUObject(this, &USessionSearchList::OnItemSelectionChanged);
	}
}

void USessionSearchList::NativeDestruct()
{
	Super::NativeDestruct();

	if (ListView_SessionSearch)
	{
		ListView_SessionSearch->OnItemSelectionChanged().RemoveAll(this);
	}
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

void USessionSearchList::OnItemSelectionChanged(UObject* Item)
{
	if (USessionSearchListItemObject* ListItemObject = Cast<USessionSearchListItemObject>(Item))
	{
		if (USessionSearchResultViewModel* SessionSearchResultViewModel = ListItemObject->SessionSearchResultViewModel)
		{
			if (SessionSettingPanel)
			{
				SessionSettingPanel->SetSessionSettings(SessionSearchResultViewModel->SessionSearchResult.SessionSettings);
			}
		}
	}
}

void USessionSearchList::OnFindSessionsStart_Implementation()
{
}

void USessionSearchList::OnFindSessionsComplete_Implementation()
{
}
