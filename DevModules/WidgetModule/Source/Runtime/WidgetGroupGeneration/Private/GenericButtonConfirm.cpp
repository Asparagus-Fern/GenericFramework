// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericButtonConfirm.h"

#include "GenericButtonWidget.h"

UGenericButtonCollection* UGenericButtonConfirm::GetButtonCollection() const
{
	return ButtonCollection.IsValid() ? ButtonCollection.Get() : nullptr;
}

void UGenericButtonConfirm::SetButtonCollection(UGenericButtonCollection* InButtonCollection)
{
	ButtonCollection = InButtonCollection;
}

UGenericButtonGroup* UGenericButtonConfirm::GetButtonGroup() const
{
	return ButtonGroup.IsValid() ? ButtonGroup.Get() : nullptr;
}

void UGenericButtonConfirm::SetButtonGroup(UGenericButtonGroup* InButtonGroup)
{
	ButtonGroup = InButtonGroup;
}

UGenericButtonWidget* UGenericButtonConfirm::GetButtonWidget() const
{
	return IsValid(GetOuter()) ? Cast<UGenericButtonWidget>(GetOuter()) : nullptr;
}

void UGenericButtonConfirm::ConfirmButtonPressed()
{
	ConfirmButtonPressedEvent.ExecuteIfBound();
}

void UGenericButtonConfirm::ConfirmButtonReleased()
{
	ConfirmButtonReleasedEvent.ExecuteIfBound();
}

void UGenericButtonConfirm::ConfirmButtonHovered()
{
	ConfirmButtonHoveredEvent.ExecuteIfBound();
}

void UGenericButtonConfirm::ConfirmButtonUnhovered()
{
	ConfirmButtonUnhoveredEvent.ExecuteIfBound();
}

void UGenericButtonConfirm::ConfirmButtonClicked()
{
	ConfirmButtonClickedEvent.ExecuteIfBound();
}

void UGenericButtonConfirm::ConfirmButtonDoubleClicked()
{
	ConfirmButtonDoubleClickedEvent.ExecuteIfBound();
}

void UGenericButtonConfirm::ConfirmButtonSelection(bool bInSelected)
{
	ConfirmSelectionChangedEvent.ExecuteIfBound(bInSelected);
}
