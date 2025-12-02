// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonWidget.h"

#include "WidgetType.h"
#include "Binding/States/WidgetStateRegistration.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "MVVM/ButtonInputViewModel.h"
#include "MVVM/ButtonSelectionViewModel.h"
#include "MVVM/ButtonSoundViewModel.h"
#include "Style/GenericButtonStyle.h"
#include "UWidget/GenericButton.h"

/* ==================== UInteractableWidgetBase ==================== */

UGenericButtonWidget::UGenericButtonWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	  , bButtonEnabled(true)
	  , bInteractionEnabled(true)
	  , bLocked(false)
	  , bSelectable(true)
	  , bToggleable(false)
	  , bSelectedWhenReceiveFocus(false)
	  , bTriggerClickedAfterSelection(false)
	  , bSelected(false)
	  , MinWidth(0)
	  , MinHeight(0)
{
	SetButtonFocusable(true);
}

/* ==================== UUserWidget ==================== */

void UGenericButtonWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UGenericButtonWidget::SetIsEnabled(bool bInIsEnabled)
{
	const bool bValueChanged = bButtonEnabled != bInIsEnabled;

	bool bOldBroadcastState = bShouldBroadcastState;
	bShouldBroadcastState = false;

	if (bInIsEnabled)
	{
		Super::SetIsEnabled(bInIsEnabled);
		EnableButton();
	}
	else
	{
		Super::SetIsEnabled(bInIsEnabled);
		DisableButton();
	}

	bShouldBroadcastState = bOldBroadcastState;

	if (bValueChanged)
	{
		// Note: State is disabled, so we broadcast !bIsEnabled
		BroadcastBinaryPostStateChange(UWidgetDisabledStateRegistration::Bit, !bInIsEnabled);
	}
}

bool UGenericButtonWidget::IsHovered() const
{
	Super::IsHovered();
	return RootButton.IsValid() && RootButton->IsButtonHovered();
}

bool UGenericButtonWidget::Initialize()
{
	const bool bInitializedThisCall = Super::Initialize();

	if (bInitializedThisCall)
	{
		UGenericButton* RootButtonRaw = ConstructInternalButton();

		RootButtonRaw->SetClickMethod(ClickMethod);
		RootButtonRaw->SetTouchMethod(TouchMethod);
		RootButtonRaw->SetPressMethod(PressMethod);
		RootButtonRaw->SetButtonFocusable(IsFocusable());
		RootButtonRaw->SetButtonEnabled(bButtonEnabled);
		RootButtonRaw->SetInteractionEnabled(bInteractionEnabled);
		RootButton = RootButtonRaw;

		if (WidgetTree->RootWidget)
		{
			UButtonSlot* NewSlot = Cast<UButtonSlot>(RootButtonRaw->AddChild(WidgetTree->RootWidget));
			NewSlot->SetPadding(FMargin());
			NewSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);
			NewSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		}

		WidgetTree->RootWidget = RootButtonRaw;

		RootButton->OnClicked.AddUniqueDynamic(this, &UGenericButtonWidget::HandleButtonClicked);
		RootButton->OnDoubleClicked.AddUniqueDynamic(this, &UGenericButtonWidget::HandleButtonDoubleClicked);
		RootButton->OnReceivedFocus.AddUniqueDynamic(this, &UGenericButtonWidget::HandleFocusReceived);
		RootButton->OnLostFocus.AddUniqueDynamic(this, &UGenericButtonWidget::HandleFocusLost);
		RootButton->OnPressed.AddUniqueDynamic(this, &UGenericButtonWidget::HandleButtonPressed);
		RootButton->OnReleased.AddUniqueDynamic(this, &UGenericButtonWidget::HandleButtonReleased);
	}

	return bInitializedThisCall;
}

void UGenericButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	BuildStyles();
}

void UGenericButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UGenericButtonWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UNREGISTER_MVVM_PROPERTY(ButtonSelectionViewModel)
	UNREGISTER_MVVM_PROPERTY(ButtonInputViewModel)
	UNREGISTER_MVVM_PROPERTY(ButtonSoundViewModel)
}

bool UGenericButtonWidget::NativeIsInteractable() const
{
	// If it's enabled, it's "interactable" from a UMG perspective. 
	// For now this is how we generate friction on the analog cursor, which we still want for disabled buttons since they have tooltips.
	return GetIsEnabled();
}

FReply UGenericButtonWidget::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	FReply Reply = Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

	HandleFocusReceived();

	return Reply;
}

void UGenericButtonWidget::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);

	HandleFocusLost();
}

void UGenericButtonWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (!InMouseEvent.IsTouchEvent())
	{
		Super::NativeOnMouseEnter(InGeometry, InMouseEvent);

		if (GetIsEnabled() && bInteractionEnabled)
		{
			SetButtonHoveredInternal();
		}
	}
}

void UGenericButtonWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	if (!InMouseEvent.IsTouchEvent())
	{
		Super::NativeOnMouseLeave(InMouseEvent);

		if (GetIsEnabled() && bInteractionEnabled)
		{
			SetButtonUnhoveredInternal();
		}
	}
}

bool UGenericButtonWidget::GetButtonFocusable() const
{
	return IsFocusable();
}

void UGenericButtonWidget::SetButtonFocusable(bool bInIsFocusable)
{
	SetIsFocusable(bInIsFocusable);

	if (RootButton.IsValid())
	{
		RootButton->SetButtonFocusable(bInIsFocusable);
	}
}

FGameplayTag UGenericButtonWidget::GetButtonTag() const
{
	return SelfTag;
}

void UGenericButtonWidget::SetButtonTag(const FGameplayTag& InButtonTag)
{
	SelfTag = InButtonTag;
}

UGenericButton* UGenericButtonWidget::ConstructInternalButton()
{
	return WidgetTree->ConstructWidget<UGenericButton>(UGenericButton::StaticClass(), FName(TEXT("GenericButton")));
}

/* ==================== Input ==================== */

void UGenericButtonWidget::SetClickMethod(EButtonClickMethod::Type InClickMethod)
{
	ClickMethod = InClickMethod;
	if (RootButton.IsValid())
	{
		RootButton->SetClickMethod(ClickMethod);
	}
}

void UGenericButtonWidget::SetTouchMethod(EButtonTouchMethod::Type InTouchMethod)
{
	TouchMethod = InTouchMethod;
	if (RootButton.IsValid())
	{
		RootButton->SetTouchMethod(InTouchMethod);
	}
}

void UGenericButtonWidget::SetPressMethod(EButtonPressMethod::Type InPressMethod)
{
	PressMethod = InPressMethod;
	if (RootButton.IsValid())
	{
		RootButton->SetPressMethod(InPressMethod);
	}
}

UButtonInputViewModel* UGenericButtonWidget::GetButtonInputViewModel() const
{
	return ButtonInputViewModel;
}

void UGenericButtonWidget::SetButtonInputViewModel(UButtonInputViewModel* InViewModel)
{
	UNREGISTER_MVVM_PROPERTY(ButtonInputViewModel)

	ButtonInputViewModel = InViewModel;

	if (ButtonInputViewModel)
	{
		REGISTER_MVVM_PROPERTY(ButtonInputViewModel, ClickMethod, OnClickMethodChanged, true)
		REGISTER_MVVM_PROPERTY(ButtonInputViewModel, TouchMethod, OnTouchMethodChanged, true)
		REGISTER_MVVM_PROPERTY(ButtonInputViewModel, PressMethod, OnPressMethodChanged, true)
	}
}

void UGenericButtonWidget::OnClickMethodChanged_Implementation(EButtonClickMethod::Type InClickMethod)
{
	SetClickMethod(InClickMethod);
}

void UGenericButtonWidget::OnTouchMethodChanged_Implementation(EButtonTouchMethod::Type InTouchMethod)
{
	SetTouchMethod(InTouchMethod);
}

void UGenericButtonWidget::OnPressMethodChanged_Implementation(EButtonPressMethod::Type InPressMethod)
{
	SetPressMethod(InPressMethod);
}

/* ==================== Interaction ==================== */

bool UGenericButtonWidget::GetIsInteractionEnabled() const
{
	ESlateVisibility Vis = GetVisibility(); // hidden or collapsed should have 'bInteractionEnabled' set false, but sometimes they don't :(
	return GetIsEnabled() && bButtonEnabled && bInteractionEnabled && (Vis != ESlateVisibility::Collapsed) && (Vis != ESlateVisibility::Hidden);
}

void UGenericButtonWidget::SetIsInteractionEnabled(bool bInIsInteractionEnabled)
{
	if (bInteractionEnabled == bInIsInteractionEnabled)
	{
		return;
	}

	const bool bWasHovered = IsHovered();

	bInteractionEnabled = bInIsInteractionEnabled;

	if (bInteractionEnabled)
	{
		// If this is a selected and not-toggleable button, don't enable root button interaction
		if (!GetIsSelected() || bToggleable)
		{
			RootButton->SetInteractionEnabled(true);
		}
	}
	else
	{
		RootButton->SetInteractionEnabled(false);
	}

	// If the hover state changed due to an interactability change, trigger internal logic accordingly.
	const bool bIsHoveredNow = IsHovered();
	if (bWasHovered != bIsHoveredNow)
	{
		if (bIsHoveredNow)
		{
			SetButtonHoveredInternal();;
		}
		else
		{
			SetButtonUnhoveredInternal();
		}
	}
}

void UGenericButtonWidget::EnableButton()
{
	if (!bButtonEnabled)
	{
		bButtonEnabled = true;
		RootButton->SetButtonEnabled(true);

		SetButtonStyle();

		NativeOnEnabled();
	}
}

void UGenericButtonWidget::DisableButton()
{
	if (bButtonEnabled)
	{
		bButtonEnabled = false;
		RootButton->SetButtonEnabled(false);

		SetButtonStyle();

		NativeOnDisabled();
	}
}

/* ==================== Event ==================== */

void UGenericButtonWidget::SimulateButtonPressed()
{
	HandleButtonPressed();
}

void UGenericButtonWidget::SimulateButtonReleased()
{
	HandleButtonReleased();
}

void UGenericButtonWidget::SimulateButtonClicked()
{
	HandleButtonClicked();
}

void UGenericButtonWidget::SimulateButtonDoubleClicked()
{
	HandleButtonClicked();
}

void UGenericButtonWidget::SimulateButtonFocusReceived()
{
	HandleFocusReceived();
}

void UGenericButtonWidget::SimulateButtonFocusLost()
{
	HandleFocusLost();
}

void UGenericButtonWidget::HandleButtonPressed()
{
	SetButtonPressedInternal();
}

void UGenericButtonWidget::HandleButtonReleased()
{
	SetButtonReleasedInternal();
}

void UGenericButtonWidget::HandleButtonClicked()
{
	// Since the button enabled state is part of UInteractableWidgetBase, UButton::OnClicked can be fired while this button is not interactable.
	// Guard against this case.
	if (GetIsInteractionEnabled())
	{
		if (bTriggerClickedAfterSelection)
		{
			SetIsSelected(!bSelected);
			SetButtonClickedInternal();
		}
		else
		{
			SetButtonClickedInternal();
			SetIsSelected(!bSelected);
		}
	}
}

void UGenericButtonWidget::HandleButtonDoubleClicked()
{
	SetButtonDoubleClickedInternal();
}

void UGenericButtonWidget::HandleFocusReceived()
{
	if (bSelectedWhenReceiveFocus && !GetIsSelected())
	{
		SetIsSelected(true);
	}
	NativeOnFocusReceived();
}

void UGenericButtonWidget::HandleFocusLost()
{
	NativeOnFocusLost();
}

/* ==================== Selection ==================== */

bool UGenericButtonWidget::GetIsLocked() const
{
	return bLocked;
}

void UGenericButtonWidget::SetIsLocked(bool bInIsLocked)
{
	if (bInIsLocked != bLocked)
	{
		bLocked = bInIsLocked;

		SetButtonStyle();

		NativeOnLockedChanged(bLocked);
	}
}

bool UGenericButtonWidget::GetIsSelectable() const
{
	return bSelectable;
}

void UGenericButtonWidget::SetIsSelectable(bool bInIsSelectable)
{
	if (bInIsSelectable != bSelectable)
	{
		bSelectable = bInIsSelectable;

		if (bSelected && !bInIsSelectable)
		{
			SetSelectedInternal(false);
		}
	}
}

bool UGenericButtonWidget::GetIsToggleable() const
{
	return bToggleable;
}

void UGenericButtonWidget::SetIsToggleable(bool bInIsToggleable)
{
	bToggleable = bInIsToggleable;

	if (!GetIsSelected() || bToggleable)
	{
		RootButton->SetInteractionEnabled(bInteractionEnabled);
	}
	else if (GetIsSelected() && !bToggleable)
	{
		RootButton->SetInteractionEnabled(bInteractableWhenSelected);
	}
}

bool UGenericButtonWidget::GetIsDefaultSelected() const
{
	return bDefaultSelected;
}

void UGenericButtonWidget::SetIsDefaultSelected(bool bInDefaultSelected)
{
	if (bDefaultSelected != bInDefaultSelected)
	{
		bDefaultSelected = bInDefaultSelected;
	}
}

bool UGenericButtonWidget::GetIsSelectedWhenReceiveFocus() const
{
	return bSelectedWhenReceiveFocus;
}

void UGenericButtonWidget::SetIsSelectedWhenReceiveFocus(bool bInSelectedWhenReceiveFocus)
{
	if (ensure(bSelectable || !bInSelectedWhenReceiveFocus))
	{
		bSelectedWhenReceiveFocus = bInSelectedWhenReceiveFocus;
	}
}

bool UGenericButtonWidget::GetIsInteractableWhenSelected() const
{
	return bInteractableWhenSelected;
}

void UGenericButtonWidget::SetIsInteractableWhenSelected(bool bInInteractableWhenSelected)
{
	if (bInInteractableWhenSelected != bInteractableWhenSelected)
	{
		bInteractableWhenSelected = bInInteractableWhenSelected;
		if (GetIsSelected() && !bToggleable)
		{
			SetIsInteractionEnabled(bInInteractableWhenSelected);
		}
	}
}

bool UGenericButtonWidget::GetIsTriggerClickedAfterSelection() const
{
	return bTriggerClickedAfterSelection;
}

void UGenericButtonWidget::SetIsTriggerClickedAfterSelection(bool bInTriggerClickedAfterSelection)
{
	if (bTriggerClickedAfterSelection != bInTriggerClickedAfterSelection)
	{
		bTriggerClickedAfterSelection = bInTriggerClickedAfterSelection;
	}
}

bool UGenericButtonWidget::GetIsSelected() const
{
	return bSelected;
}

void UGenericButtonWidget::SetIsSelected(bool InSelected)
{
	const bool bWasHovered = IsHovered();

	if (bSelectable && bSelected != InSelected)
	{
		if (!InSelected && bToggleable)
		{
			SetSelectedInternal(false);
		}
		else if (InSelected)
		{
			// Only allow a sound if we weren't just clicked
			SetSelectedInternal(true);
		}
	}

	// If the hover state changed due to a selection change, trigger internal logic accordingly.
	const bool bIsHoveredNow = IsHovered();
	if (bWasHovered != bIsHoveredNow)
	{
		if (bIsHoveredNow)
		{
			SetButtonHoveredInternal();;
		}
		else
		{
			SetButtonUnhoveredInternal();
		}
	}
}

UButtonSelectionViewModel* UGenericButtonWidget::GetButtonSelectionViewModel() const
{
	return ButtonSelectionViewModel;
}

void UGenericButtonWidget::SetButtonSelectionViewModel(UButtonSelectionViewModel* InViewModel)
{
	UNREGISTER_MVVM_PROPERTY(ButtonSelectionViewModel)

	ButtonSelectionViewModel = InViewModel;

	if (ButtonSelectionViewModel)
	{
		REGISTER_MVVM_PROPERTY(ButtonSelectionViewModel, bSelectable, OnSelectableChanged, true)
		REGISTER_MVVM_PROPERTY(ButtonSelectionViewModel, bToggleable, OnToggleableChanged, true)
		REGISTER_MVVM_PROPERTY(ButtonSelectionViewModel, bDefaultSelected, OnDefaultSelectedChanged, true)
		REGISTER_MVVM_PROPERTY(ButtonSelectionViewModel, bShouldSelectUponReceivingFocus, OnShouldSelectUponReceivingFocusChanged, true)
		REGISTER_MVVM_PROPERTY(ButtonSelectionViewModel, bInteractableWhenSelected, OnInteractableWhenSelectedChanged, true)
		REGISTER_MVVM_PROPERTY(ButtonSelectionViewModel, bTriggerClickedAfterSelection, OnTriggerClickedAfterSelectionChanged, true)
	}
}

void UGenericButtonWidget::OnSelectableChanged_Implementation(bool IsSelectable)
{
	SetIsSelectable(IsSelectable);
}

void UGenericButtonWidget::OnToggleableChanged_Implementation(bool IsToggleable)
{
	SetIsToggleable(IsToggleable);
}

void UGenericButtonWidget::OnDefaultSelectedChanged_Implementation(bool IsDefaultSelected)
{
	SetIsDefaultSelected(IsDefaultSelected);
}

void UGenericButtonWidget::OnShouldSelectUponReceivingFocusChanged_Implementation(bool IsShouldSelectUponReceivingFocus)
{
	SetIsSelectedWhenReceiveFocus(IsShouldSelectUponReceivingFocus);
}

void UGenericButtonWidget::OnInteractableWhenSelectedChanged_Implementation(bool IsInteractableWhenSelected)
{
	SetIsInteractableWhenSelected(IsInteractableWhenSelected);
}

void UGenericButtonWidget::OnTriggerClickedAfterSelectionChanged_Implementation(bool IsTriggerClickedAfterSelection)
{
	SetIsTriggerClickedAfterSelection(IsTriggerClickedAfterSelection);
}

/* ==================== Event Confirm ==================== */

void UGenericButtonWidget::SetButtonPressedInternal()
{
	if (OnButtonPressedConfirmedEvent.IsBound())
	{
		if (OnButtonPressedConfirmedEvent.Execute(this))
		{
			OnButtonPressedInternal();
		}
	}
	else
	{
		if (CanButtonPressedInternal())
		{
			OnButtonPressedInternal();
		}
	}
}

bool UGenericButtonWidget::CanButtonPressedInternal()
{
	return true;
}

void UGenericButtonWidget::OnButtonPressedInternal()
{
	NativeOnPressed();
}

void UGenericButtonWidget::SetButtonReleasedInternal()
{
	if (OnButtonReleasedConfirmedEvent.IsBound())
	{
		if (OnButtonReleasedConfirmedEvent.Execute(this))
		{
			OnButtonReleasedInternal();
		}
	}
	else
	{
		if (CanButtonReleasedInternal())
		{
			OnButtonReleasedInternal();
		}
	}
}

bool UGenericButtonWidget::CanButtonReleasedInternal()
{
	return true;
}

void UGenericButtonWidget::OnButtonReleasedInternal()
{
	NativeOnReleased();
}

void UGenericButtonWidget::SetButtonHoveredInternal()
{
	if (OnButtonHoveredConfirmedEvent.IsBound())
	{
		if (OnButtonHoveredConfirmedEvent.Execute(this))
		{
			OnButtonHoveredInternal();
		}
	}
	else
	{
		if (CanButtonHoveredInternal())
		{
			OnButtonHoveredInternal();
		}
	}
}

bool UGenericButtonWidget::CanButtonHoveredInternal()
{
	return true;
}

void UGenericButtonWidget::OnButtonHoveredInternal()
{
	NativeOnHovered();
}

void UGenericButtonWidget::SetButtonUnhoveredInternal()
{
	if (OnButtonUnhoveredConfirmedEvent.IsBound())
	{
		if (OnButtonUnhoveredConfirmedEvent.Execute(this))
		{
			OnButtonUnhoveredInternal();
		}
	}
	else
	{
		if (CanButtonUnhoveredInternal())
		{
			OnButtonUnhoveredInternal();
		}
	}
}

bool UGenericButtonWidget::CanButtonUnhoveredInternal()
{
	return true;
}

void UGenericButtonWidget::OnButtonUnhoveredInternal()
{
	NativeOnUnhovered();
}

void UGenericButtonWidget::SetButtonClickedInternal()
{
	if (OnButtonClickedConfirmedEvent.IsBound())
	{
		if (OnButtonClickedConfirmedEvent.Execute(this))
		{
			OnButtonClickedInternal();
		}
	}
	else
	{
		if (CanButtonClickedInternal())
		{
			OnButtonClickedInternal();
		}
	}
}

bool UGenericButtonWidget::CanButtonClickedInternal()
{
	return true;
}

void UGenericButtonWidget::OnButtonClickedInternal()
{
	NativeOnClicked();
}

void UGenericButtonWidget::SetButtonDoubleClickedInternal()
{
	if (OnButtonDoubleClickedConfirmedEvent.IsBound())
	{
		if (OnButtonDoubleClickedConfirmedEvent.Execute(this))
		{
			OnButtonDoubleClickedInternal();
		}
	}
	else
	{
		if (CanButtonDoubleClickedInternal())
		{
			OnButtonDoubleClickedInternal();
		}
	}
}

bool UGenericButtonWidget::CanButtonDoubleClickedInternal()
{
	return true;
}

void UGenericButtonWidget::OnButtonDoubleClickedInternal()
{
	NativeOnDoubleClicked();
}

void UGenericButtonWidget::SetSelectedInternal(bool bInSelected)
{
	if (OnButtonSelectionConfirmedEvent.IsBound())
	{
		if (OnButtonSelectionConfirmedEvent.Execute(this, bInSelected))
		{
			OnButtonSelectionInternal(bInSelected);
		}
	}
	else
	{
		if (CanButtonSelectionInternal(bInSelected))
		{
			OnButtonSelectionInternal(bInSelected);
		}
	}
}

bool UGenericButtonWidget::CanButtonSelectionInternal(bool bInSelected)
{
	return true;
}

void UGenericButtonWidget::OnButtonSelectionInternal(bool bInSelected)
{
	const bool bValueChanged = bInSelected != bSelected;

	bSelected = bInSelected;

	SetButtonStyle();

	if (bSelected)
	{
		NativeOnSelected();

		if (!bToggleable && IsInteractable())
		{
			// If the button isn't toggleable, then disable interaction with the root button while selected
			// The prevents us getting unnecessary click noises and events
			RootButton->SetInteractionEnabled(bInteractableWhenSelected);
		}
	}
	else
	{
		// Once deselected, restore the root button interactivity to the desired state
		RootButton->SetInteractionEnabled(bInteractionEnabled);

		NativeOnDeselected();
	}

	if (bValueChanged)
	{
		BroadcastBinaryPostStateChange(UWidgetSelectedStateRegistration::Bit, bSelected);
	}
}

/* ==================== Event Handle ==================== */

void UGenericButtonWidget::NativeOnEnabled()
{
	HandleOnButtonEnabled();
	OnButtonEnabled.Broadcast(this);
	NativeOnButtonStyleChanged();
}

void UGenericButtonWidget::NativeOnDisabled()
{
	HandleOnButtonDisabled();
	OnButtonDisabled.Broadcast(this);
	NativeOnButtonStyleChanged();
}

void UGenericButtonWidget::NativeOnPressed()
{
	HandleOnButtonPressed();
	OnButtonPressed.Broadcast(this);
	BroadcastBinaryPostStateChange(UWidgetPressedStateRegistration::Bit, true);
}

void UGenericButtonWidget::NativeOnReleased()
{
	HandleOnButtonReleased();
	OnButtonReleased.Broadcast(this);
	BroadcastBinaryPostStateChange(UWidgetPressedStateRegistration::Bit, false);
}

void UGenericButtonWidget::NativeOnHovered()
{
	HandleOnButtonHovered();
	OnButtonHovered.Broadcast(this);

	Invalidate(EInvalidateWidgetReason::Layout);

	NativeOnButtonStyleChanged();

	BroadcastBinaryPostStateChange(UWidgetHoveredStateRegistration::Bit, true);

	if (!GetIsSelected() && HoveredAnimation)
	{
		PlayAnimationForward(HoveredAnimation);
	}
}

void UGenericButtonWidget::NativeOnUnhovered()
{
	HandleOnButtonUnhovered();
	OnButtonUnhovered.Broadcast(this);

	Invalidate(EInvalidateWidgetReason::Layout);

	NativeOnButtonStyleChanged();

	BroadcastBinaryPostStateChange(UWidgetHoveredStateRegistration::Bit, false);

	if (!GetIsSelected() && HoveredAnimation)
	{
		PlayAnimationReverse(HoveredAnimation);
	}
}

void UGenericButtonWidget::NativeOnClicked()
{
	if (!GetIsLocked())
	{
		HandleOnButtonClicked();
		OnButtonClicked.Broadcast(this);
	}
	else
	{
		HandleOnButtonLockClicked();
		OnButtonLockClicked.Broadcast(this);
	}
}

void UGenericButtonWidget::NativeOnDoubleClicked()
{
	if (!GetIsLocked())
	{
		HandleOnButtonDoubleClicked();
		OnButtonDoubleClicked.Broadcast(this);
	}
	else
	{
		HandleOnButtonLockDoubleClicked();
		OnButtonLockDoubleClicked.Broadcast(this);
	}
}

void UGenericButtonWidget::NativeOnSelected()
{
	HandleOnButtonSelectionChanged(true);
	OnButtonSelectionChanged.Broadcast(this, true);
	NativeOnButtonStyleChanged();

	if (SelectedAnimation)
	{
		PlayAnimationForward(SelectedAnimation);
	}
}

void UGenericButtonWidget::NativeOnDeselected()
{
	HandleOnButtonSelectionChanged(false);
	OnButtonSelectionChanged.Broadcast(this, false);
	NativeOnButtonStyleChanged();

	if (SelectedAnimation)
	{
		PlayAnimationReverse(SelectedAnimation);
	}
}

void UGenericButtonWidget::NativeOnFocusReceived()
{
	HandleOnButtonFocusReceived();
	OnButtonFocusReceived.Broadcast(this);
}

void UGenericButtonWidget::NativeOnFocusLost()
{
	HandleOnButtonFocusLost();
	OnButtonFocusLost.Broadcast(this);
}

void UGenericButtonWidget::NativeOnLockedChanged(bool bIsLocked)
{
	HandleOnButtonLockedChanged(bIsLocked);
	OnButtonLockedChanged.Broadcast(this, bIsLocked);
}

void UGenericButtonWidget::NativeOnLockClicked()
{
	HandleOnButtonLockClicked();
	OnButtonLockClicked.Broadcast(this);
}

void UGenericButtonWidget::NativeOnLockDoubleClicked()
{
	HandleOnButtonLockDoubleClicked();
	OnButtonLockDoubleClicked.Broadcast(this);
}

void UGenericButtonWidget::NativeOnButtonStyleChanged()
{
	HandleOnButtonStyleChanged();
	OnButtonStyleChanged.Broadcast(this);
}

/* ==================== Style ==================== */

void UGenericButtonWidget::SetMinWidth(int32 InMinWidth)
{
	MinWidth = InMinWidth;
	RefreshDimensions();
}

void UGenericButtonWidget::SetMinHeight(int32 InMinHeight)
{
	MinHeight = InMinHeight;
	RefreshDimensions();
}

void UGenericButtonWidget::RefreshDimensions() const
{
	if (RootButton.IsValid())
	{
		RootButton->SetMinDesiredWidth(MinWidth);
		RootButton->SetMinDesiredHeight(MinHeight);
	}
}

const UGenericButtonStyle* UGenericButtonWidget::GetStyleCDO(const TSubclassOf<UGenericButtonStyle>& InClass) const
{
	if (InClass)
	{
		if (const UGenericButtonStyle* GenericButtonStyle = Cast<UGenericButtonStyle>(InClass->ClassDefaultObject))
		{
			return GenericButtonStyle;
		}
	}
	return nullptr;
}

void UGenericButtonWidget::UpdateInternalStyle(const TSubclassOf<UGenericButtonStyle>& InClass, FButtonStyle& OutStyle) const
{
	if (const UGenericButtonStyle* StyleCDO = GetStyleCDO(InClass))
	{
		StyleCDO->GetButtonStyle(OutStyle);
	}
}

void UGenericButtonWidget::BuildStyles()
{
#define UPDATE_INTERNAL_STYLE(StyleClass) \
	UpdateInternalStyle(StyleClass, Internal##StyleClass);

	UPDATE_INTERNAL_STYLE(NormalStyle)
	UPDATE_INTERNAL_STYLE(SelectedStyle)
	UPDATE_INTERNAL_STYLE(LockedStyle)
	UPDATE_INTERNAL_STYLE(DisabledStyle)

#undef UPDATE_INTERNAL_STYLE

#define UPDATE_INTERNAL_STYLE_HOVERED_SOUND_OVERRIDE(Style, HoveredSlateSoundOverride, PressedSlateSoundOverride) \
	if (IsValid(HoveredSlateSoundOverride.GetResourceObject())){Style.HoveredSlateSound = HoveredSlateSoundOverride;} \
	if (IsValid(PressedSlateSoundOverride.GetResourceObject())){Style.PressedSlateSound = PressedSlateSoundOverride;}

	UPDATE_INTERNAL_STYLE_HOVERED_SOUND_OVERRIDE(InternalNormalStyle, HoveredSlateSoundOverride, PressedSlateSoundOverride)
	UPDATE_INTERNAL_STYLE_HOVERED_SOUND_OVERRIDE(InternalSelectedStyle, SelectedHoveredSlateSoundOverride, SelectedPressedSlateSoundOverride)
	UPDATE_INTERNAL_STYLE_HOVERED_SOUND_OVERRIDE(InternalLockedStyle, LockedHoveredSlateSoundOverride, LockedPressedSlateSoundOverride)

#undef UPDATE_INTERNAL_STYLE_HOVERED_SOUND

	SetButtonStyle();
	RefreshDimensions();
}

void UGenericButtonWidget::SetButtonStyle()
{
	if (UButton* ButtonPtr = RootButton.Get())
	{
		const FButtonStyle* UseStyle = nullptr;

		if (IsDesignTime())
		{
#if WITH_EDITOR
			if (DesiredButtonStyle == EDesiredButtonStyle::Normal)
			{
				UseStyle = &InternalNormalStyle;
			}
			else if (DesiredButtonStyle == EDesiredButtonStyle::Selected)
			{
				UseStyle = &InternalSelectedStyle;
			}
			else if (DesiredButtonStyle == EDesiredButtonStyle::Locked)
			{
				UseStyle = &InternalLockedStyle;
			}
			else if (DesiredButtonStyle == EDesiredButtonStyle::Disabled)
			{
				UseStyle = &InternalDisabledStyle;
			}
#endif
		}
		else
		{
			if (bLocked)
			{
				UseStyle = &InternalLockedStyle;
			}
			else if (bSelected)
			{
				UseStyle = &InternalSelectedStyle;
			}
			else if (bButtonEnabled)
			{
				UseStyle = &InternalNormalStyle;
			}
			else
			{
				UseStyle = &InternalDisabledStyle;
			}
		}

		ButtonPtr->SetStyle(*UseStyle);
		NativeOnButtonStyleChanged();
	}
}

/* ==================== Sound ==================== */

void UGenericButtonWidget::SetHoveredSoundOverride(USoundBase* Sound)
{
	if (HoveredSlateSoundOverride.GetResourceObject() != Sound)
	{
		HoveredSlateSoundOverride.SetResourceObject(Sound);
		BuildStyles();
	}
}

void UGenericButtonWidget::SetHoveredSlateSoundOverride(const FSlateSound& Sound)
{
	if (HoveredSlateSoundOverride.GetResourceObject() != Sound.GetResourceObject())
	{
		HoveredSlateSoundOverride.SetResourceObject(Sound.GetResourceObject());
		BuildStyles();
	}
}

void UGenericButtonWidget::SetPressedSoundOverride(USoundBase* Sound)
{
	if (PressedSlateSoundOverride.GetResourceObject() != Sound)
	{
		PressedSlateSoundOverride.SetResourceObject(Sound);
		BuildStyles();
	}
}

void UGenericButtonWidget::SetPressedSlateSoundOverride(const FSlateSound& Sound)
{
	if (PressedSlateSoundOverride.GetResourceObject() != Sound.GetResourceObject())
	{
		PressedSlateSoundOverride.SetResourceObject(Sound.GetResourceObject());
		BuildStyles();
	}
}

void UGenericButtonWidget::SetSelectedHoveredSoundOverride(USoundBase* Sound)
{
	if (SelectedHoveredSlateSoundOverride.GetResourceObject() != Sound)
	{
		SelectedHoveredSlateSoundOverride.SetResourceObject(Sound);
		BuildStyles();
	}
}

void UGenericButtonWidget::SetSelectedHoveredSlateSoundOverride(const FSlateSound& Sound)
{
	if (SelectedHoveredSlateSoundOverride.GetResourceObject() != Sound.GetResourceObject())
	{
		SelectedHoveredSlateSoundOverride.SetResourceObject(Sound.GetResourceObject());
		BuildStyles();
	}
}

void UGenericButtonWidget::SetSelectedPressedSoundOverride(USoundBase* Sound)
{
	if (SelectedPressedSlateSoundOverride.GetResourceObject() != Sound)
	{
		SelectedPressedSlateSoundOverride.SetResourceObject(Sound);
		BuildStyles();
	}
}

void UGenericButtonWidget::SetSelectedPressedSlateSoundOverride(const FSlateSound& Sound)
{
	if (SelectedPressedSlateSoundOverride.GetResourceObject() != Sound.GetResourceObject())
	{
		SelectedPressedSlateSoundOverride.SetResourceObject(Sound.GetResourceObject());
		BuildStyles();
	}
}

void UGenericButtonWidget::SetLockedHoveredSoundOverride(USoundBase* Sound)
{
	if (LockedHoveredSlateSoundOverride.GetResourceObject() != Sound)
	{
		LockedHoveredSlateSoundOverride.SetResourceObject(Sound);
		BuildStyles();
	}
}

void UGenericButtonWidget::SetLockedHoveredSlateSoundOverride(const FSlateSound& Sound)
{
	if (LockedHoveredSlateSoundOverride.GetResourceObject() != Sound.GetResourceObject())
	{
		LockedHoveredSlateSoundOverride.SetResourceObject(Sound.GetResourceObject());
		BuildStyles();
	}
}

void UGenericButtonWidget::SetLockedPressedSoundOverride(USoundBase* Sound)
{
	if (LockedPressedSlateSoundOverride.GetResourceObject() != Sound)
	{
		LockedPressedSlateSoundOverride.SetResourceObject(Sound);
		BuildStyles();
	}
}

void UGenericButtonWidget::SetLockedPressedSlateSoundOverride(const FSlateSound& Sound)
{
	if (LockedPressedSlateSoundOverride.GetResourceObject() != Sound.GetResourceObject())
	{
		LockedPressedSlateSoundOverride.SetResourceObject(Sound.GetResourceObject());
		BuildStyles();
	}
}

UButtonSoundViewModel* UGenericButtonWidget::GetButtonSoundViewModel() const
{
	return ButtonSoundViewModel;
}

void UGenericButtonWidget::SetButtonSoundViewModel(UButtonSoundViewModel* InViewModel)
{
	UNREGISTER_MVVM_PROPERTY(ButtonSoundViewModel)

	ButtonSoundViewModel = InViewModel;

	if (ButtonSoundViewModel)
	{
		REGISTER_MVVM_PROPERTY(ButtonSoundViewModel, HoveredSlateSoundOverride, OnHoveredSlateSoundOverrideChanged, true)
		REGISTER_MVVM_PROPERTY(ButtonSoundViewModel, PressedSlateSoundOverride, OnPressedSlateSoundOverrideChanged, true)
		REGISTER_MVVM_PROPERTY(ButtonSoundViewModel, SelectedHoveredSlateSoundOverride, OnSelectedHoveredSlateSoundOverrideChanged, true)
		REGISTER_MVVM_PROPERTY(ButtonSoundViewModel, SelectedPressedSlateSoundOverride, OnSelectedPressedSlateSoundOverrideChanged, true)
		REGISTER_MVVM_PROPERTY(ButtonSoundViewModel, LockedHoveredSlateSoundOverride, OnLockedHoveredSlateSoundOverrideChanged, true)
		REGISTER_MVVM_PROPERTY(ButtonSoundViewModel, LockedPressedSlateSoundOverride, OnLockedPressedSlateSoundOverrideChanged, true)
	}
}

void UGenericButtonWidget::OnHoveredSlateSoundOverrideChanged_Implementation(FSlateSound InSlateSound)
{
	SetHoveredSlateSoundOverride(InSlateSound);
}

void UGenericButtonWidget::OnPressedSlateSoundOverrideChanged_Implementation(FSlateSound InSlateSound)
{
	SetPressedSlateSoundOverride(InSlateSound);
}

void UGenericButtonWidget::OnSelectedHoveredSlateSoundOverrideChanged_Implementation(FSlateSound InSlateSound)
{
	SetSelectedHoveredSlateSoundOverride(InSlateSound);
}

void UGenericButtonWidget::OnSelectedPressedSlateSoundOverrideChanged_Implementation(FSlateSound InSlateSound)
{
	SetSelectedPressedSlateSoundOverride(InSlateSound);
}

void UGenericButtonWidget::OnLockedHoveredSlateSoundOverrideChanged_Implementation(FSlateSound InSlateSound)
{
	SetLockedHoveredSlateSoundOverride(InSlateSound);
}

void UGenericButtonWidget::OnLockedPressedSlateSoundOverrideChanged_Implementation(FSlateSound InSlateSound)
{
	SetLockedPressedSlateSoundOverride(InSlateSound);
}
