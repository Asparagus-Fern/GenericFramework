// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyListItem.h"

#include "PropertyType.h"
#include "Components/TextBlock.h"
#include "UMG/PropertyValue/PropertyValueBase.h"
#include "UMG/Spawner/PropertyValueSpawner.h"

void UPropertyListItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	if (UPropertyListItemObject* PropertyListItemObject = GetListItem<UPropertyListItemObject>())
	{
		if (Text_PropertyName)
		{
			Text_PropertyName->SetText(PropertyListItemObject->PropertyDisplayName);
		}

		if (PropertyValueSpawner)
		{
			if (PropertyValueSpawner->SpawnPropertyWidget(PropertyListItemObject->PropertyValueClass, PropertyListItemObject->PropertyValueViewModel))
			{
				PropertyListItemObject->PropertyValueViewModel->Initialize();
			}
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
}
