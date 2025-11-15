// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "UMG/SessionSearchListItem.h"

#include "WidgetType.h"
#include "ViewModel/SessionSearchResultViewModel.h"

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

void USessionSearchListItem::OnSessionSearchResultViewModelSet_Implementation(USessionSearchResultViewModel* InViewModel)
{
}
