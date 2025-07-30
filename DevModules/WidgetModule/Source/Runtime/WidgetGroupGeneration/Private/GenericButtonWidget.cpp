// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonWidget.h"

#include "CommonButtonBase.h"
#include "Binding/States/WidgetStateRegistration.h"
#include "Blueprint/WidgetTree.h"
#include "BPFunctions/BPFunctions_File.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Style/GenericButtonStyle.h"
#include "UWidget/GenericButton.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Button, "UI.Button");

/* ==================== UInteractableWidgetBase ==================== */

UGenericButtonWidget::UGenericButtonWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	  , MinWidth(0)
	  , MinHeight(0)
	  , bLocked(false)
	  , bSelectable(true)
	  , bToggleable(false)
	  , bSelectedWhenReceiveFocus(false)
	  , bTriggerClickedAfterSelection(false)
	  , bSelected(false)
	  , bButtonEnabled(true)
	  , bInteractionEnabled(true)
{
	SetButtonFocusable(true);
}

/* ==================== UUserWidget ==================== */

void UGenericButtonWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	RefreshDimensions();
	BuildStyles();
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
			NativeOnHovered();
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
			NativeOnUnhovered();
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

void UGenericButtonWidget::NativeConstructButtonParameters(const FButtonParameter& ButtonParameter)
{
	ConstructButtonParameters(ButtonParameter);

	SetToolTipText(ButtonParameter.DescriptionParameter.TooltipText);

	SetVisibility(ButtonParameter.RenderParameter.Visibility);
	SetRenderTransformPivot(ButtonParameter.RenderParameter.RenderTransformPivot);
	SetRenderTransform(ButtonParameter.RenderParameter.RenderTransform);

	SetIsSelectable(ButtonParameter.SelectionParameter.bSelectable);
	SetIsToggleable(ButtonParameter.SelectionParameter.bToggleable);
	SetIsDefaultSelected(ButtonParameter.SelectionParameter.bDefaultSelected);
	SetIsSelectedWhenReceiveFocus(ButtonParameter.SelectionParameter.bShouldSelectUponReceivingFocus);
	SetIsInteractableWhenSelected(ButtonParameter.SelectionParameter.bInteractableWhenSelected);
	SetIsTriggerClickedAfterSelection(ButtonParameter.SelectionParameter.bTriggerClickedAfterSelection);

	SetClickMethod(ButtonParameter.InputParameter.ClickMethod);
	SetTouchMethod(ButtonParameter.InputParameter.TouchMethod);
	SetPressMethod(ButtonParameter.InputParameter.PressMethod);
}

UGenericButton* UGenericButtonWidget::ConstructInternalButton()
{
	return WidgetTree->ConstructWidget<UGenericButton>(UGenericButton::StaticClass(), FName(TEXT("GenericButton")));
}

/* ==================== Event ==================== */

void UGenericButtonWidget::HandleButtonClicked()
{
	// Since the button enabled state is part of UInteractableWidgetBase, UButton::OnClicked can be fired while this button is not interactable.
	// Guard against this case.
	if (GetIsInteractionEnabled())
	{
		if (bTriggerClickedAfterSelection)
		{
			SetIsSelected(!bSelected, false);
			NativeOnClicked();
		}
		else
		{
			NativeOnClicked();
			SetIsSelected(!bSelected, false);
		}
	}
}

void UGenericButtonWidget::HandleButtonDoubleClicked()
{
	NativeOnDoubleClicked();
}

void UGenericButtonWidget::HandleFocusReceived()
{
	if (bSelectedWhenReceiveFocus && !GetIsSelected())
	{
		SetIsSelected(true, false);
	}
	NativeOnFocusReceived();
}

void UGenericButtonWidget::HandleFocusLost()
{
	NativeOnFocusLost();
}

void UGenericButtonWidget::HandleButtonPressed()
{
	NativeOnPressed();
}

void UGenericButtonWidget::HandleButtonReleased()
{
	NativeOnReleased();
}

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
		OutStyle.Normal = StyleCDO->Normal;
		OutStyle.Hovered = StyleCDO->Hovered;
		OutStyle.Pressed = StyleCDO->Pressed;
		OutStyle.Disabled = StyleCDO->Disabled;
		OutStyle.NormalForeground = StyleCDO->NormalForeground;
		OutStyle.HoveredForeground = StyleCDO->HoveredForeground;
		OutStyle.PressedForeground = StyleCDO->PressedForeground;
		OutStyle.DisabledForeground = StyleCDO->DisabledForeground;
		OutStyle.HoveredSlateSound = StyleCDO->HoveredSlateSound;
		OutStyle.PressedSlateSound = StyleCDO->PressedSlateSound;
		OutStyle.NormalPadding = StyleCDO->NormalPadding;
		OutStyle.PressedPadding = StyleCDO->PressedPadding;
	}
}

void UGenericButtonWidget::BuildStyles()
{
#define UPDATE_INTERNAL_STYLE(StyleClass) \
	UpdateInternalStyle(StyleClass,Internal##StyleClass);

	UPDATE_INTERNAL_STYLE(NormalStyle)
	UPDATE_INTERNAL_STYLE(SelectedStyle)
	UPDATE_INTERNAL_STYLE(LockedStyle)
	UPDATE_INTERNAL_STYLE(DisabledStyle)

#undef UPDATE_INTERNAL_STYLE

	SetButtonStyle();
	RefreshDimensions();
}

void UGenericButtonWidget::SetButtonStyle()
{
	if (UButton* ButtonPtr = RootButton.Get())
	{
		const FButtonStyle* UseStyle;
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
		ButtonPtr->SetStyle(*UseStyle);
		NativeOnButtonStyleChanged();
	}
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

		BroadcastBinaryPostStateChange(UWidgetLockedStateRegistration::Bit, bLocked);
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

void UGenericButtonWidget::SetIsSelected(bool InSelected, bool bGiveClickFeedback)
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
			SetSelectedInternal(true, bGiveClickFeedback);
		}
	}

	// If the hover state changed due to a selection change, trigger internal logic accordingly.
	const bool bIsHoveredNow = IsHovered();
	if (bWasHovered != bIsHoveredNow)
	{
		if (bIsHoveredNow)
		{
			NativeOnHovered();
		}
		else
		{
			NativeOnUnhovered();
		}
	}
}

void UGenericButtonWidget::SetSelectedInternal(bool bInSelected, bool bGiveClickFeedback /**= true*/, bool bBroadcast /**= true*/)
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

		if (bGiveClickFeedback)
		{
			// Selection was not triggered by a button click, so play the click sound
			FSlateApplication::Get().PlaySound(InternalNormalStyle.PressedSlateSound);
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
			NativeOnHovered();
		}
		else
		{
			NativeOnUnhovered();
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
