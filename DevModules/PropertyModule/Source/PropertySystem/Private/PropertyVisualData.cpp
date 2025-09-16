// Copyright ChenTaiye 2025. All Rights Reserved.

#include "PropertyVisualData.h"

#include "MVVM/PropertyViewModel.h"

TSubclassOf<UPropertyValueBase> UPropertyVisualData::GatherListItemForProperty(const UPropertyViewModel* InPropertyViewModel) const
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
