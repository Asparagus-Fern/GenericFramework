// Copyright ChenTaiye 2025. All Rights Reserved.


#include "PropertyListItemAsset.h"

#include "UMG/PropertyListItem.h"

#if WITH_EDITOR

void UPropertyListItemAsset::Generate()
{
	TArray<UPropertyListItemObject*> Result;
	GeneratePropertyListItemObjects(Result);

	TArray<FName> PropertyNames;
	for (const auto& ItemObject : PropertyListItemObjects)
	{
		PropertyNames.Add(ItemObject->PropertyName);
	}

	for (auto& ItemObject : Result)
	{
		if (!PropertyNames.Contains(ItemObject->PropertyName))
		{
			PropertyListItemObjects.Add(ItemObject);
		}
	}
}

#endif

void UPropertyListItemAsset::GeneratePropertyListItemObjects(TArray<UPropertyListItemObject*>& Result)
{
}
