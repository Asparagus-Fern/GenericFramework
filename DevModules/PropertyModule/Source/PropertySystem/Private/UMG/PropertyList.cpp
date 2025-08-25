// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyList.h"

#include "PropertyType.h"
#include "DataAsset/PropertyListItemAsset.h"
#include "UMG/PropertyListItem.h"
#include "UWidget/GenericListView.h"

void UPropertyList::NativePreConstruct()
{
	Super::NativePreConstruct();
	UpdatePropertyListView();
}

void UPropertyList::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPropertyList::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPropertyList::SetPropertyListItemAsset(UPropertyListItemAsset* InAsset)
{
	if (!IsValid(InAsset))
	{
		GenericLOG(GenericLogProperty, Error, TEXT("InAsset Is InValid"))
		return;
	}

	PropertyListItemAsset = InAsset;
	UpdatePropertyListView();
}

void UPropertyList::UpdatePropertyListView()
{
	if (GenericListView_Property)
	{
		GenericListView_Property->ClearListItems();

		if (PropertyListItemAsset)
		{
			for (auto& PropertyListItemObject : PropertyListItemAsset->PropertyListItemObjects)
			{
				if (!IsDesignTime())
				{
					PropertyListItemObjects.Add(PropertyListItemObject);
				}

				GenericListView_Property->AddItem(PropertyListItemObject);
			}
		}
	}
}
