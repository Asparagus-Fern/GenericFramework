// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Widget/PropertyVisualData.h"

#include "Base/PropertyEntity.h"
#include "Widget/ListEntry/PropertyListEntryBase.h"

TSubclassOf<UPropertyListEntryBase> UPropertyVisualData::GetEntryForProperty(UPropertyEntity* InProperty)
{
	if (!InProperty)
	{
		return TSubclassOf<UPropertyListEntryBase>();
	}

	if (const TSubclassOf<UPropertyListEntryBase> EntryWidgetClassPtr = EntryWidgetForName.FindRef(InProperty->GetPropertyName()))
	{
		return EntryWidgetClassPtr;
	}

	for (UClass* Class = InProperty->GetClass(); Class; Class = Class->GetSuperClass())
	{
		if (TSubclassOf<UPropertyEntity> PropertyClass = TSubclassOf<UPropertyEntity>(Class))
		{
			if (const TSubclassOf<UPropertyListEntryBase> EntryWidgetClassPtr = EntryWidgetForClass.FindRef(PropertyClass))
			{
				return EntryWidgetClassPtr;
			}
		}
	}

	return TSubclassOf<UPropertyListEntryBase>();
}
