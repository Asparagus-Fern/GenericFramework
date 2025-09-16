// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyListItem.h"

#include "PropertyType.h"
#include "WidgetType.h"
#include "Components/TextBlock.h"
#include "MVVM/PropertyViewModel.h"
#include "UMG/PropertyValue/PropertyValueBase.h"
#include "UMG/Spawner/PropertyValueSpawner.h"

void UPropertyListItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	if (UPropertyListItemObject* PropertyListItemObject = GetListItem<UPropertyListItemObject>())
	{
		PropertyViewModel = PropertyListItemObject->PropertyViewModel;

		REGISTER_MVVM_PROPERTY(PropertyViewModel, PropertyDisplayName, OnPropertyDisplayNameChanged, true)

		if (PropertyValueSpawner)
		{
			PropertyValueSpawner->SpawnPropertyWidget(PropertyListItemObject->PropertyValueClass, PropertyViewModel);
		}
	}
}

void UPropertyListItem::NativeOnItemSelectionChanged(bool bIsSelected)
{
	IUserObjectListEntry::NativeOnItemSelectionChanged(bIsSelected);
}

void UPropertyListItem::NativeOnItemExpansionChanged(bool bIsExpanded)
{
	IUserObjectListEntry::NativeOnItemExpansionChanged(bIsExpanded);
}

void UPropertyListItem::NativeOnEntryReleased()
{
	IUserObjectListEntry::NativeOnEntryReleased();

	if (PropertyViewModel)
	{
		PropertyViewModel->RemoveAllFieldValueChangedDelegates(this);
	}
}

void UPropertyListItem::OnPropertyDisplayNameChanged_Implementation(const FText& InDisplayName)
{
	if (Text_PropertyName)
	{
		Text_PropertyName->SetText(InDisplayName);
	}
}
