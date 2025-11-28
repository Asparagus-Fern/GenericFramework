// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "UMG/SessionSearchListItem.h"

#include "GenericButtonWidget.h"
#include "GenericSessionSubsystem.h"
#include "WidgetType.h"
#include "ViewModel/SessionSearchResultViewModel.h"

void USessionSearchListItem::NativeConstruct()
{
	Super::NativeConstruct();

	if (GenericButtonWidget_Join)
	{
		GenericButtonWidget_Join->OnButtonClicked.AddUniqueDynamic(this, &USessionSearchListItem::OnJoinButtonClicked);
		GenericButtonWidget_Join->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USessionSearchListItem::NativeDestruct()
{
	Super::NativeDestruct();

	if (GenericButtonWidget_Join)
	{
		GenericButtonWidget_Join->OnButtonClicked.RemoveAll(this);
	}
}

void USessionSearchListItem::OnJoinButtonClicked(UGenericButtonWidget* InButton)
{
	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(this))
	{
		if (SessionSearchResultViewModel)
		{
			GenericSessionSubsystem->JoinSession(GetOwningPlayer(), SessionSearchResultViewModel->SessionSearchResult);
		}
	}
}

void USessionSearchListItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	if (USessionSearchListItemObject* Object = Cast<USessionSearchListItemObject>(ListItemObject))
	{
		SetSessionSearchResultViewModel(Object->SessionSearchResultViewModel);
	}
}

void USessionSearchListItem::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);

	if (bIsSelected)
	{
		RefreshSelectedSession();
	}

	if (GenericButtonWidget_Join)
	{
		GenericButtonWidget_Join->SetVisibility(bIsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void USessionSearchListItem::NativeOnItemExpansionChanged(bool bIsExpanded)
{
	IUserObjectListEntry::NativeOnItemExpansionChanged(bIsExpanded);
}

void USessionSearchListItem::NativeOnEntryReleased()
{
	IUserObjectListEntry::NativeOnEntryReleased();
	SetSessionSearchResultViewModel(nullptr);
}

void USessionSearchListItem::SetSessionSearchResultViewModel(USessionSearchResultViewModel* InViewModel)
{
	UNREGISTER_MVVM_PROPERTY(SessionSearchResultViewModel);

	SessionSearchResultViewModel = InViewModel;

	if (SessionSearchResultViewModel)
	{
		OnSessionSearchResultViewModelSet(SessionSearchResultViewModel);
	}
}

void USessionSearchListItem::RefreshSelectedSession()
{
	if (UGenericSessionSubsystem* GenericSessionSubsystem = UGenericSessionSubsystem::Get(this))
	{
		/* FOnlineSessionNull 对 FindSessionByID 没有实现 */
		GenericSessionSubsystem->FindSingleSession
		(
			GetOwningPlayer(),
			SessionSearchResultViewModel->SessionSearchResult.OwnerPlayerID,
			FOnSingleSessionResultCompleteDelegate::CreateUObject(this, &USessionSearchListItem::OnRefreshSelectedSessionComplete)
		);
	}
}

void USessionSearchListItem::OnRefreshSelectedSessionComplete(int32 InPlayerIndex, bool bWasSuccessful, const FOnlineSessionSearchResult& InResult)
{
	if (bWasSuccessful)
	{
		SessionSearchResultViewModel->SetSessionSearchResult(InResult);
	}

	if (IsListItemSelected())
	{
		RefreshSelectedSession();
	}
}

void USessionSearchListItem::OnSessionSearchResultViewModelSet_Implementation(USessionSearchResultViewModel* InViewModel)
{
}
