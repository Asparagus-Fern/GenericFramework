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

USessionSearchResultViewModel* USessionSearchListItem::GetSessionSearchResultViewModel()
{
	return SessionSearchResultViewModel;
}

void USessionSearchListItem::SetSessionSearchResultViewModel(USessionSearchResultViewModel* InViewModel)
{
	UNREGISTER_MVVM_PROPERTY(SessionSearchResultViewModel);

	SessionSearchResultViewModel = InViewModel;

	if (SessionSearchResultViewModel)
	{
		REGISTER_MVVM_PROPERTY(SessionSearchResultViewModel, PingInMs, OnPingInMsChanged, true)
		REGISTER_MVVM_PROPERTY(SessionSearchResultViewModel, UniqueIdRepl, OnUniqueIdReplChanged, true)
		REGISTER_MVVM_PROPERTY(SessionSearchResultViewModel, OwningUserName, OnOwningUserNameChanged, true)
		REGISTER_MVVM_PROPERTY(SessionSearchResultViewModel, SessionSettings, OnSessionSettingsChanged, true)
		REGISTER_MVVM_PROPERTY(SessionSearchResultViewModel, NumOpenPrivateConnections, OnNumOpenPrivateConnectionsChanged, true)
		REGISTER_MVVM_PROPERTY(SessionSearchResultViewModel, NumOpenPublicConnections, OnNumOpenPublicConnectionsChanged, true)
	}
}

void USessionSearchListItem::OnPingInMsChanged_Implementation(int32 InPingInMs)
{
}

void USessionSearchListItem::OnUniqueIdReplChanged_Implementation(FUniqueNetIdRepl InUniqueIdRepl)
{
}

void USessionSearchListItem::OnOwningUserNameChanged_Implementation(const FString& InOwningUserName)
{
}

void USessionSearchListItem::OnSessionSettingsChanged_Implementation(USessionSettingsViewModel* InSessionSettings)
{
	SessionSettingsViewModel = InSessionSettings;
}

void USessionSearchListItem::OnNumOpenPrivateConnectionsChanged_Implementation(int32 InNumOpenPrivateConnections)
{
}

void USessionSearchListItem::OnNumOpenPublicConnectionsChanged_Implementation(int32 InNumOpenPublicConnections)
{
}
