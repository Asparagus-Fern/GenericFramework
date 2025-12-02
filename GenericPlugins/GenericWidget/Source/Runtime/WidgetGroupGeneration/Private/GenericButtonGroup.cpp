// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonGroup.h"

#include "GenericButtonCollection.h"
#include "GenericButtonContainer.h"
#include "GenericButtonWidget.h"
#include "WidgetType.h"
#include "MVVM/ButtonGroupViewModel.h"
#include "Type/DebugType.h"

void UGenericButtonGroup::NativeOnCreate()
{
	IStateInterface::NativeOnCreate();

	ButtonCollection = IsValid(GetOuter()) ? Cast<UGenericButtonCollection>(GetOuter()) : nullptr;
}

void UGenericButtonGroup::NativeOnDestroy()
{
	IStateInterface::NativeOnDestroy();
}

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

	InButton->GetOnButtonPressedConfirmedEvent().BindUObject(this, &UGenericButtonGroup::HandleOnButtonPressedConfirmed);
	InButton->GetOnButtonReleasedConfirmedEvent().BindUObject(this, &UGenericButtonGroup::HandleOnButtonReleasedConfirmed);
	InButton->GetOnButtonHoveredConfirmedEvent().BindUObject(this, &UGenericButtonGroup::HandleOnButtonHoveredConfirmed);
	InButton->GetOnButtonUnhoveredConfirmedEvent().BindUObject(this, &UGenericButtonGroup::HandleOnButtonUnhoveredConfirmed);
	InButton->GetOnButtonClickedConfirmedEvent().BindUObject(this, &UGenericButtonGroup::HandleOnButtonClickedConfirmed);
	InButton->GetOnButtonDoubleClickedConfirmedEvent().BindUObject(this, &UGenericButtonGroup::HandleOnButtonDoubleClickedConfirmed);
	InButton->GetOnButtonSelectionConfirmedEvent().BindUObject(this, &UGenericButtonGroup::HandleOnButtonSelectionConfirmed);

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

	InButton->OnButtonPressed.RemoveAll(this);
	InButton->OnButtonReleased.RemoveAll(this);
	InButton->OnButtonHovered.RemoveAll(this);
	InButton->OnButtonUnhovered.RemoveAll(this);
	InButton->OnButtonClicked.RemoveAll(this);
	InButton->OnButtonDoubleClicked.RemoveAll(this);
	InButton->OnButtonSelectionChanged.RemoveAll(this);

	InButton->GetOnButtonPressedConfirmedEvent().Unbind();
	InButton->GetOnButtonReleasedConfirmedEvent().Unbind();
	InButton->GetOnButtonHoveredConfirmedEvent().Unbind();
	InButton->GetOnButtonUnhoveredConfirmedEvent().Unbind();
	InButton->GetOnButtonClickedConfirmedEvent().Unbind();
	InButton->GetOnButtonDoubleClickedConfirmedEvent().Unbind();
	InButton->GetOnButtonSelectionConfirmedEvent().Unbind();
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

	InButton->SetSelectedInternal(true);
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

FGameplayTag UGenericButtonGroup::GetSelectedButtonTag() const
{
	if (UGenericButtonWidget* Button = GetSelectedButton())
	{
		return Button->GetButtonTag();
	}
	return FGameplayTag::EmptyTag;
}

void UGenericButtonGroup::SetSelectedButtonByTag(FGameplayTag InTag)
{
	for (auto& Button : ButtonWidgets)
	{
		if (Button->GetButtonTag() == InTag)
		{
			SetSelectedButton(Button);
			return;
		}
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
		SelectedButton->SetSelectedInternal(false);
		LastSelectedButton = SelectedButton;
		SelectedButton = nullptr;
	}
}

bool UGenericButtonGroup::HandleOnButtonPressedConfirmed(UGenericButtonWidget* InButton)
{
	bool Result = true;

	Result &= InButton->CanButtonPressedInternal();
	if (SelectedButton && SelectedButton != InButton)
	{
		Result &= SelectedButton->CanButtonPressedInternal();
	}

	return Result;
}

bool UGenericButtonGroup::HandleOnButtonReleasedConfirmed(UGenericButtonWidget* InButton)
{
	bool Result = true;

	Result &= InButton->CanButtonReleasedInternal();
	if (SelectedButton && SelectedButton != InButton)
	{
		Result &= SelectedButton->CanButtonReleasedInternal();
	}

	return Result;
}

bool UGenericButtonGroup::HandleOnButtonHoveredConfirmed(UGenericButtonWidget* InButton)
{
	bool Result = true;

	Result &= InButton->CanButtonHoveredInternal();
	if (SelectedButton && SelectedButton != InButton)
	{
		Result &= SelectedButton->CanButtonHoveredInternal();
	}

	return Result;
}

bool UGenericButtonGroup::HandleOnButtonUnhoveredConfirmed(UGenericButtonWidget* InButton)
{
	bool Result = true;

	Result &= InButton->CanButtonUnhoveredInternal();
	if (SelectedButton && SelectedButton != InButton)
	{
		Result &= SelectedButton->CanButtonUnhoveredInternal();
	}

	return Result;
}

bool UGenericButtonGroup::HandleOnButtonClickedConfirmed(UGenericButtonWidget* InButton)
{
	bool Result = true;

	Result &= InButton->CanButtonClickedInternal();
	if (SelectedButton && SelectedButton != InButton)
	{
		Result &= SelectedButton->CanButtonClickedInternal();
	}

	return Result;
}

bool UGenericButtonGroup::HandleOnButtonDoubleClickedConfirmed(UGenericButtonWidget* InButton)
{
	bool Result = true;

	Result &= InButton->CanButtonDoubleClickedInternal();
	if (SelectedButton && SelectedButton != InButton)
	{
		Result &= SelectedButton->CanButtonDoubleClickedInternal();
	}

	return Result;
}

bool UGenericButtonGroup::HandleOnButtonSelectionConfirmed(UGenericButtonWidget* InButton, bool InSelection)
{
	bool Result = true;

	Result &= InButton->CanButtonSelectionInternal(InSelection);
	if (SelectedButton && SelectedButton != InButton)
	{
		Result &= SelectedButton->CanButtonSelectionInternal(false);
	}

	return Result;
}

void UGenericButtonGroup::HandleOnButtonPressed_Implementation(UGenericButtonWidget* InButton)
{
	OnButtonPressed.Broadcast(this, InButton);
}

void UGenericButtonGroup::HandleOnButtonReleased_Implementation(UGenericButtonWidget* InButton)
{
	OnButtonReleased.Broadcast(this, InButton);
}

void UGenericButtonGroup::HandleOnButtonHovered_Implementation(UGenericButtonWidget* InButton)
{
	OnButtonHovered.Broadcast(this, InButton);
}

void UGenericButtonGroup::HandleOnButtonUnhovered_Implementation(UGenericButtonWidget* InButton)
{
	OnButtonUnhovered.Broadcast(this, InButton);
}

void UGenericButtonGroup::HandleOnButtonClicked_Implementation(UGenericButtonWidget* InButton)
{
	OnButtonClicked.Broadcast(this, InButton);
}

void UGenericButtonGroup::HandleOnButtonDoubleClicked_Implementation(UGenericButtonWidget* InButton)
{
	OnButtonDoubleClicked.Broadcast(this, InButton);
}

void UGenericButtonGroup::HandleOnButtonSelectionChanged_Implementation(UGenericButtonWidget* InButton, bool Selection)
{
	/* Button State Already Changed In Button Widget, Here Is Sync Button State And Broadcast */
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

UGenericButtonCollection* UGenericButtonGroup::GetButtonCollection() const
{
	return ButtonCollection.IsValid() ? ButtonCollection.Get() : nullptr;
}

UButtonGroupViewModel* UGenericButtonGroup::GetButtonGroupViewModel()
{
	return ButtonGroupViewModel;
}

void UGenericButtonGroup::SetButtonGroupViewModel(UButtonGroupViewModel* InButtonGroupViewModel)
{
	if (ButtonGroupViewModel)
	{
		ButtonGroupViewModel->RemoveAllFieldValueChangedDelegates(this);
	}

	ButtonGroupViewModel = InButtonGroupViewModel;

	if (ButtonGroupViewModel)
	{
	}
}
