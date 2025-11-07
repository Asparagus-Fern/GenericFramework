// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "UMG/SessionSearchList.h"

#include "NetworkType.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystemUtils.h"
#include "WidgetType.h"
#include "Components/ListView.h"
#include "GameFramework/PlayerState.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Type/DebugType.h"
#include "UMG/SessionSearchListItem.h"
#include "ViewModel/SessionSearchListViewModel.h"
#include "ViewModel/SessionSearchResultViewModel.h"

void USessionSearchList::NativeConstruct()
{
	Super::NativeConstruct();
}

void USessionSearchList::NativeDestruct()
{
	Super::NativeDestruct();
}

USessionSearchListViewModel* USessionSearchList::GetSessionSearchListViewModel()
{
	return SessionSearchListViewModel;
}

void USessionSearchList::SetSessionSearchListViewModel(USessionSearchListViewModel* InViewModel)
{
	UNREGISTER_MVVM_PROPERTY(SessionSearchListViewModel);
	if (SessionSearchListViewModel)
	{
		SessionSearchListViewModel->GetOnGetSessionSearchResultEvent().RemoveAll(this);
		SessionSearchListViewModel->GetOnGetPageSessionSearchResultEvent().RemoveAll(this);
	}

	SessionSearchListViewModel = InViewModel;

	if (SessionSearchListViewModel)
	{
		SessionSearchListViewModel->GetOnGetSessionSearchResultEvent().AddUObject(this, &USessionSearchList::OnGetSessionSearchResult);
		SessionSearchListViewModel->GetOnGetPageSessionSearchResultEvent().AddUObject(this, &USessionSearchList::OnGetPageSessionSearchResult);

		REGISTER_MVVM_PROPERTY(SessionSearchListViewModel, SessionState, OnSessionStateChanged, true)
		REGISTER_MVVM_PROPERTY(SessionSearchListViewModel, ItemsPerPage, OnItemsPerPageChanged, true)
		REGISTER_MVVM_PROPERTY(SessionSearchListViewModel, PageIndex, OnPageIndexChanged, true)
	}
}

void USessionSearchList::OnSessionStateChanged_Implementation(ESessionState InSessionState)
{
	if (ListView_SessionSearch)
	{
		if (InSessionState == ESessionState::InProgress)
		{
		}
		else if (InSessionState == ESessionState::Done)
		{
		}
		else if (InSessionState == ESessionState::Failed)
		{
		}
		else if (InSessionState == ESessionState::Cancel)
		{
		}
	}
}

void USessionSearchList::OnItemsPerPageChanged_Implementation(int32 InItemsPerPage)
{
}

void USessionSearchList::OnPageIndexChanged_Implementation(int32 InPageIndex)
{
}

void USessionSearchList::OnGetSessionSearchResult(const TArray<FOnlineSessionSearchResult>& InResults)
{
}

void USessionSearchList::OnGetPageSessionSearchResult(const TArray<FOnlineSessionSearchResult>& InResults)
{
	if (ListView_SessionSearch)
	{
		ListView_SessionSearch->ClearListItems();

		for (auto& Result : InResults)
		{
			USessionSearchListItemObject* NewItemObject = NewObject<USessionSearchListItemObject>(this);
			USessionSearchResultViewModel* NewResultViewModel = NewObject<USessionSearchResultViewModel>(this);

			NewResultViewModel->Initialize(Result);
			NewItemObject->SessionSearchResultViewModel = NewResultViewModel;

			if (ListView_SessionSearch)
			{
				ListView_SessionSearch->AddItem(NewItemObject);
			}
		}
	}
}
