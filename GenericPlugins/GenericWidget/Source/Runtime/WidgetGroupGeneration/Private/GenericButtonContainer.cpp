// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonContainer.h"

#include "Components/PanelWidget.h"

void UGenericButtonContainer::OnChildAdded_Implementation(UUserWidget* InWidget, int32 InIndex)
{
	Super::OnChildAdded_Implementation(InWidget, InIndex);
	Panel_Container->AddChild(InWidget);
}

void UGenericButtonContainer::OnChildRemoved_Implementation(UUserWidget* InWidget, int32 InIndex)
{
	Super::OnChildRemoved_Implementation(InWidget, InIndex);
	Panel_Container->RemoveChild(InWidget);
}

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
