// Copyright ChenTaiye 2025. All Rights Reserved.


#include "GenericButtonGroup.h"

#include "GenericButtonWidget.h"
#include "Debug/DebugType.h"

UGenericButtonContainer* UGenericButtonGroup::GetButtonGroupWidget()
{
	return ButtonGroupWidget;
}

void UGenericButtonGroup::SetButtonGroupWidget(UGenericButtonContainer* InButtonGroupWidget)
{
	ButtonGroupWidget = InButtonGroupWidget;
}

void UGenericButtonGroup::AddButtons(const TArray<UGenericButtonWidget*>& InButtons)
{
	for (const auto& Button : InButtons)
	{
		AddButton(Button);
	}
}

void UGenericButtonGroup::AddButton(UGenericButtonWidget* InButton)
{
	if (!IsValid(InButton))
	{
		GenericLOG(GenericLogUI, Error, TEXT("Button Is InValid"))
		return;
	}

	ButtonWidgets.Add(InButton);

	InButton->OnButtonPressed.AddUniqueDynamic(this, &UGenericButtonGroup::HandleOnButtonPressed);
	InButton->OnButtonReleased.AddUniqueDynamic(this, &UGenericButtonGroup::HandleOnButtonReleased);
	InButton->OnButtonHovered.AddUniqueDynamic(this, &UGenericButtonGroup::HandleOnButtonHovered);
	InButton->OnButtonUnhovered.AddUniqueDynamic(this, &UGenericButtonGroup::HandleOnButtonUnhovered);
	InButton->OnButtonClicked.AddUniqueDynamic(this, &UGenericButtonGroup::HandleOnButtonClicked);
	InButton->OnButtonDoubleClicked.AddUniqueDynamic(this, &UGenericButtonGroup::HandleOnButtonDoubleClicked);
	InButton->OnButtonSelectionChanged.AddUniqueDynamic(this, &UGenericButtonGroup::HandleOnButtonSelectionChanged);

	if (!HasSelectedButton() && InButton->bDefaultSelected)
	{
		SetSelectedButton(InButton);
	}
}

void UGenericButtonGroup::RemoveButtons(const TArray<UGenericButtonWidget*>& InButtons)
{
	for (const auto& Button : InButtons)
	{
		RemoveButton(Button);
	}
}

void UGenericButtonGroup::RemoveButtonByIndex(int32 InIndex)
{
	if (UGenericButtonWidget* Button = GetButtonByIndex(InIndex))
	{
		RemoveButton(Button);
	}
	else
	{
		GenericLOG(GenericLogUI, Warning, TEXT("Index Is InValid"))
	}
}

void UGenericButtonGroup::RemoveButton(UGenericButtonWidget* InButton)
{
	if (!IsValid(InButton))
	{
		GenericLOG(GenericLogUI, Error, TEXT("Button Is InValid"))
		return;
	}

	if (!ButtonWidgets.Contains(InButton))
	{
		GenericLOG(GenericLogUI, Error, TEXT("This Button Is Not In This Group"))
		return;
	}

	if (GetSelectedButton() == InButton)
	{
		DeselectAll();
	}

	ButtonWidgets.Remove(InButton);
}

void UGenericButtonGroup::ClearAllButton()
{
	if (IsValid(SelectedButton))
	{
		DeselectAll();
	}

	ButtonWidgets.Reset();
	SelectedButton = nullptr;
	LastSelectedButton = nullptr;
}

TArray<UGenericButtonWidget*> UGenericButtonGroup::GetAllButton() const
{
	return ButtonWidgets;
}

int32 UGenericButtonGroup::GetButtonCount() const
{
	return ButtonWidgets.Num();
}

bool UGenericButtonGroup::HasButton(UGenericButtonWidget* InButton) const
{
	return ButtonWidgets.Contains(InButton);
}

UGenericButtonWidget* UGenericButtonGroup::GetButtonByIndex(int32 InIndex)
{
	if (ButtonWidgets.IsValidIndex(InIndex))
	{
		return ButtonWidgets[InIndex];
	}
	return nullptr;
}

int32 UGenericButtonGroup::FindButtonIndex(UGenericButtonWidget* InButton) const
{
	int32 Index;
	ButtonWidgets.Find(InButton, Index);
	return Index;
}

bool UGenericButtonGroup::HasLastSelectedButton() const
{
	return IsValid(LastSelectedButton);
}

bool UGenericButtonGroup::HasSelectedButton() const
{
	return IsValid(SelectedButton);
}

UGenericButtonWidget* UGenericButtonGroup::GetLastSelectedButton() const
{
	return LastSelectedButton;
}

int32 UGenericButtonGroup::GetLastSelectedButtonIndex() const
{
	if (UGenericButtonWidget* Button = GetLastSelectedButton())
	{
		return FindButtonIndex(Button);
	}
	return -1;
}

UGenericButtonWidget* UGenericButtonGroup::GetSelectedButton() const
{
	return SelectedButton;
}

void UGenericButtonGroup::SetSelectedButton(UGenericButtonWidget* InButton)
{
	if (!IsValid(InButton))
	{
		GenericLOG(GenericLogUI, Error, TEXT("Button Is InValid"))
		return;
	}

	if (!InButton->bSelectable)
	{
		GenericLOG(GenericLogUI, Warning, TEXT("Button Is Disable To Selected"))
		return;
	}

	HandleOnButtonSelectionChanged(InButton, true);
}

int32 UGenericButtonGroup::GetSelectedButtonIndex() const
{
	if (UGenericButtonWidget* Button = GetSelectedButton())
	{
		return FindButtonIndex(Button);
	}
	return -1;
}

void UGenericButtonGroup::SetSelectedButtonByIndex(int32 InIndex)
{
	if (UGenericButtonWidget* Button = GetButtonByIndex(InIndex))
	{
		SetSelectedButton(Button);
	}
	else
	{
		GenericLOG(GenericLogUI, Warning, TEXT("Index Is InValid"))
	}
}

void UGenericButtonGroup::SelectLastButton()
{
	if (HasLastSelectedButton())
	{
		SetSelectedButton(LastSelectedButton);
	}
}

void UGenericButtonGroup::SelectPreviousButton(bool bAllowWrapping)
{
	if (!HasSelectedButton())
	{
		return;
	}

	const int32 PreviousIndex = GetSelectedButtonIndex() - 1;
	if (PreviousIndex >= 0)
	{
		SetSelectedButtonByIndex(PreviousIndex);
	}
	else if (bAllowWrapping)
	{
		SetSelectedButtonByIndex(GetButtonCount() - 1);
	}
}

void UGenericButtonGroup::SelectNextButton(bool bAllowWrapping)
{
	if (!HasSelectedButton())
	{
		return;
	}

	const int32 NextIndex = GetSelectedButtonIndex() + 1;
	if (NextIndex < GetButtonCount())
	{
		SetSelectedButtonByIndex(NextIndex);
	}
	else if (bAllowWrapping)
	{
		SetSelectedButtonByIndex(0);
	}
}

void UGenericButtonGroup::DeselectAll()
{
	if (HasSelectedButton())
	{
		SelectedButton->SetIsSelected(false);
		LastSelectedButton = SelectedButton;
		SelectedButton = nullptr;
	}
}

void UGenericButtonGroup::HandleOnButtonPressed(UGenericButtonWidget* InButton)
{
	OnButtonPressed.Broadcast(this, InButton);
}

void UGenericButtonGroup::HandleOnButtonReleased(UGenericButtonWidget* InButton)
{
	OnButtonReleased.Broadcast(this, InButton);
}

void UGenericButtonGroup::HandleOnButtonHovered(UGenericButtonWidget* InButton)
{
	OnButtonHovered.Broadcast(this, InButton);
}

void UGenericButtonGroup::HandleOnButtonUnhovered(UGenericButtonWidget* InButton)
{
	OnButtonUnhovered.Broadcast(this, InButton);
}

void UGenericButtonGroup::HandleOnButtonClicked(UGenericButtonWidget* InButton)
{
	OnButtonClicked.Broadcast(this, InButton);
}

void UGenericButtonGroup::HandleOnButtonDoubleClicked(UGenericButtonWidget* InButton)
{
	OnButtonDoubleClicked.Broadcast(this, InButton);
}

void UGenericButtonGroup::HandleOnButtonSelectionChanged(UGenericButtonWidget* InButton, bool Selection)
{
	if (HasSelectedButton())
	{
		if (SelectedButton == InButton)
		{
			LastSelectedButton = SelectedButton;
			SelectedButton = nullptr;
			OnButtonSelectionChanged.Broadcast(this, InButton, Selection);
		}
		else
		{
			SelectedButton->SetSelectedInternal(false);
			SelectedButton = InButton;
			OnButtonSelectionChanged.Broadcast(this, SelectedButton, Selection);
		}
	}
	else
	{
		SelectedButton = InButton;
		OnButtonSelectionChanged.Broadcast(this, SelectedButton, Selection);
	}
}
