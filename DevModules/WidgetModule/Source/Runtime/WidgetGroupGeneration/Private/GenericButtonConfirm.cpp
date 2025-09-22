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
	HandleConfirmButtonPressed();
	ConfirmButtonPressedEvent.ExecuteIfBound();
}

void UGenericButtonConfirm::ConfirmButtonReleased()
{
	HandleConfirmButtonReleased();
	ConfirmButtonReleasedEvent.ExecuteIfBound();
}

void UGenericButtonConfirm::ConfirmButtonHovered()
{
	HandleConfirmButtonHovered();
	ConfirmButtonHoveredEvent.ExecuteIfBound();
}

void UGenericButtonConfirm::ConfirmButtonUnhovered()
{
	HandleConfirmButtonUnhovered();
	ConfirmButtonUnhoveredEvent.ExecuteIfBound();
}

void UGenericButtonConfirm::ConfirmButtonClicked()
{
	HandleConfirmButtonClicked();
	ConfirmButtonClickedEvent.ExecuteIfBound();
}

void UGenericButtonConfirm::ConfirmButtonDoubleClicked()
{
	HandleConfirmButtonDoubleClicked();
	ConfirmButtonDoubleClickedEvent.ExecuteIfBound();
}

void UGenericButtonConfirm::ConfirmButtonSelection(bool bInSelected)
{
	HandleConfirmButtonSelection(bInSelected);
	ConfirmSelectionChangedEvent.ExecuteIfBound(bInSelected);
}

void UGenericButtonConfirm::HandleConfirmButtonPressed_Implementation()
{
}

void UGenericButtonConfirm::HandleConfirmButtonReleased_Implementation()
{
}

void UGenericButtonConfirm::HandleConfirmButtonHovered_Implementation()
{
}

void UGenericButtonConfirm::HandleConfirmButtonUnhovered_Implementation()
{
}

void UGenericButtonConfirm::HandleConfirmButtonClicked_Implementation()
{
}

void UGenericButtonConfirm::HandleConfirmButtonDoubleClicked_Implementation()
{
}

void UGenericButtonConfirm::HandleConfirmButtonSelection_Implementation(bool bInSelected)
{
}
