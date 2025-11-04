// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonContainer.h"

UGenericButtonCollection* UGenericButtonContainer::GetButtonCollection() const
{
	return ButtonCollection.IsValid() ? ButtonCollection.Get() : nullptr;
}

void UGenericButtonContainer::SetButtonCollection(UGenericButtonCollection* InButtonCollection)
{
	ButtonCollection = InButtonCollection;
}

UGenericButtonGroup* UGenericButtonContainer::GetButtonGroup() const
{
	return ButtonGroup.IsValid() ? ButtonGroup.Get() : nullptr;
}

void UGenericButtonContainer::SetButtonGroup(UGenericButtonGroup* InButtonGroup)
{
	ButtonGroup = InButtonGroup;
}
