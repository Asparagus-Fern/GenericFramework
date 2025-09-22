// Copyright ChenTaiye 2025. All Rights Reserved.

#include "PropertyVisualData.h"

#include "MVVM/PropertyViewModel.h"

TSubclassOf<UPropertyValueBase> UPropertyVisualData::GatherPropertyValueWidgetClass(const UPropertyViewModel* InPropertyViewModel) const
{
	if (!IsValid(InPropertyViewModel))
	{
		return nullptr;
	}

	if (PropertyValueWidgetForName.Contains(InPropertyViewModel->PropertyName))
	{
		return PropertyValueWidgetForName.FindRef(InPropertyViewModel->PropertyName);
	}

	if (PropertyValueWidgetForClass.Contains(InPropertyViewModel->GetClass()))
	{
		return PropertyValueWidgetForClass.FindRef(InPropertyViewModel->GetClass());
	}

	return nullptr;
}

TMap<FGameplayTag, TSubclassOf<UPropertyListItemOption>> UPropertyVisualData::GatherPropertyOptionClasses(const UPropertyViewModel* InPropertyViewModel) const
{
	TMap<FGameplayTag, TSubclassOf<UPropertyListItemOption>> OptionClasses;

	if (IsValid(InPropertyViewModel))
	{
		for (auto& PropertyTag : InPropertyViewModel->PropertyTags)
		{
			if (PropertyListItemOptionForName.Contains(InPropertyViewModel->PropertyName))
			{
				OptionClasses.Emplace(PropertyTag, PropertyValueWidgetForName.FindRef(InPropertyViewModel->PropertyName));
				continue;
			}

			if (PropertyListItemOptionForClass.Contains(PropertyTag))
			{
				OptionClasses.Emplace(PropertyTag, PropertyListItemOptionForClass.FindRef(PropertyTag));
				continue;
			}
		}
	}

	return OptionClasses;
}
