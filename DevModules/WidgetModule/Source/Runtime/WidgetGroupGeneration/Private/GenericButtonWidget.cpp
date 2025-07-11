// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GenericButtonWidget.h"

#include "CommonActionWidget.h"
#include "CommonUITypes.h"
#include "ICommonInputModule.h"
#include "ICommonUIModule.h"
#include "Binding/States/WidgetStateRegistration.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/ButtonSlot.h"
#include "Input/CommonUIInputTypes.h"
#include "UWidget/GenericButton.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"

#if WITH_EDITOR
#include "CommonUIEditorSettings.h"
#endif

UE_DEFINE_GAMEPLAY_TAG(TAG_Button, "UI.Button");

/* ==================== UInteractableWidgetBase ==================== */

UGenericButtonWidget::UGenericButtonWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	  , MinWidth(0)
	  , MinHeight(0)
	  , bApplyAlphaOnDisable(true)
	  , bLocked(false)
	  , bSelectable(false)
	  , bToggleable(false)
	  , bShouldSelectUponReceivingFocus(false)
	  , bTriggerClickedAfterSelection(false)
	  , bSelected(false)
	  , bRequiresHold(false)
	  , HoldTime(0.f)
	  , HoldRollbackTime(0.f)
	  , CurrentHoldTime(0.f)
	  , bDisplayInputActionWhenNotInteractable(true)
	  , bShouldUseFallbackDefaultInputAction(true)
	  , bSimulateHoverOnTouchInput(true)
	  , bButtonEnabled(true)
	  , bInteractionEnabled(true)
{
	SetButtonFocusable(true);

	if (const TSubclassOf<UCommonButtonStyle> TransparentStyleClass = LoadClass<UCommonButtonStyle>(nullptr, TEXT("/Script/Engine.Blueprint'/WidgetModule/ButtonStyle/CBS_Transparent.CBS_Transparent_C'")))
	{
		StyleClass = TransparentStyleClass;
	}
}

/* ==================== UUserWidget ==================== */

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

void UGenericButtonWidget::NativeConstruct()
{
	if (!HoldData && ICommonInputModule::GetSettings().GetDefaultHoldData())
	{
		HoldData = ICommonInputModule::GetSettings().GetDefaultHoldData();
	}

	BindTriggeringInputActionToClick();
	BindInputMethodChangedDelegate();
	UpdateInputActionWidget();

	Super::NativeConstruct();
}

void UGenericButtonWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnbindTriggeringInputActionToClick();
	UnbindInputMethodChangedDelegate();

	if (HoldTickerHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(HoldTickerHandle);
		HoldTickerHandle = nullptr;
	}
	if (HoldRollbackTickerHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(HoldRollbackTickerHandle);
		HoldRollbackTickerHandle = nullptr;
	}
}

bool UGenericButtonWidget::NativeIsInteractable() const
{
	// If it's enabled, it's "interactable" from a UMG perspective. 
	// For now this is how we generate friction on the analog cursor, which we still want for disabled buttons since they have tooltips.
	return GetIsEnabled();
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
	return RootButton.IsValid() && RootButton->IsHovered();
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

void UGenericButtonWidget::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	// GetCachedWidget()->AddMetadata<FCommonButtonMetaData>(MakeShared<FCommonButtonMetaData>(*this));
}

void UGenericButtonWidget::PostLoad()
{
	Super::PostLoad();

#if WITH_EDITOR
	// We will remove this once existing content is fixed up. Since previously the native CDO was actually the default style, this code will attempt to set the style on assets that were once using this default
	if (!StyleClass && !bStyleNoLongerNeedsConversion && !IsRunningDedicatedServer())
	{
		UCommonUIEditorSettings& Settings = ICommonUIModule::GetEditorSettings();
		Settings.ConditionalPostLoad();
		StyleClass = Settings.GetTemplateButtonStyle();
	}
	bStyleNoLongerNeedsConversion = true;
#endif
}

void UGenericButtonWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	RefreshDimensions();
	BuildStyles();
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

#if WITH_EDITOR

void UGenericButtonWidget::OnCreationFromPalette()
{
	bStyleNoLongerNeedsConversion = true;
	if (!StyleClass)
	{
		StyleClass = ICommonUIModule::GetEditorSettings().GetTemplateButtonStyle();
	}
	if (!HoldData && ICommonInputModule::GetSettings().GetDefaultHoldData())
	{
		HoldData = ICommonInputModule::GetSettings().GetDefaultHoldData();
	}
	Super::OnCreationFromPalette();
}

#endif // WITH_EDITOR

UGenericButton* UGenericButtonWidget::ConstructInternalButton()
{
	return WidgetTree->ConstructWidget<UGenericButton>(UGenericButton::StaticClass(), FName(TEXT("GenericButton")));
}

/* ==================== Event ==================== */

void UGenericButtonWidget::HandleButtonClicked()
{
	// Since the button enabled state is part of UInteractableWidgetBase, UButton::OnClicked can be fired while this button is not interactable.
	// Guard against this case.
	if (IsInteractionEnabled())
	{
		// @TODO: Current click rejection method relies on click hold time, this can be refined. See NativeOnHoldProgress.
		// Also gamepad can indirectly trigger this method, so don't guard against pressed
		if (bRequiresHold && CurrentHoldTime < HoldTime)
		{
			return;
		}

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

		HoldReset();
	}
}

void UGenericButtonWidget::HandleButtonDoubleClicked()
{
	NativeOnDoubleClicked();
}

void UGenericButtonWidget::HandleFocusReceived()
{
	if (bShouldSelectUponReceivingFocus && !GetIsSelected())
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

	const UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem();

	if (CommonInputSubsystem && CommonInputSubsystem->GetCurrentInputType() == ECommonInputType::Touch && bSimulateHoverOnTouchInput)
	{
		// Simulate hover events when using touch input
		NativeOnHovered();
	}

	if (bRequiresHold && HoldTime > 0.f)
	{
		// Note: Fires once per frame FTSTicker::AddTicker has a delay param if desired
		HoldTickerHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UGenericButtonWidget::NativeOnHoldProgress));
		if (HoldRollbackTickerHandle.IsValid())
		{
			FTSTicker::GetCoreTicker().RemoveTicker(HoldRollbackTickerHandle);
			HoldRollbackTickerHandle = nullptr;
		}
	}
	if (TriggeringBindingHandle.IsValid())
	{
		TriggeringBindingHandle.ResetHold();
	}
}

void UGenericButtonWidget::HandleButtonReleased()
{
	NativeOnReleased();

	const UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem();

	if (CommonInputSubsystem && CommonInputSubsystem->GetCurrentInputType() == ECommonInputType::Touch && bSimulateHoverOnTouchInput)
	{
		// Simulate hover events when using touch input
		NativeOnUnhovered();
	}

	if (bRequiresHold && HoldTime > 0.f)
	{
		if (HoldRollbackTime <= UE_SMALL_NUMBER)
		{
			HoldReset();
			NativeOnHoldProgress(0.f);
		}
		else
		{
			// Begin hold progress rollback
			HoldRollbackTickerHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UGenericButtonWidget::NativeOnHoldProgressRollback));

			FTSTicker::GetCoreTicker().RemoveTicker(HoldTickerHandle);
			HoldTickerHandle = nullptr;
		}
	}
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
	HoldReset();
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
	UpdateInputActionWidget();

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
	UpdateInputActionWidget();

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

void UGenericButtonWidget::NativeInputMethodChanged(ECommonInputType CurrentInputType)
{
	UpdateInputActionWidget();
	UpdateHoldData(CurrentInputType);
	HoldReset();
	NativeOnHoldActionProgressed(0.f);

	HandleOnButtonInputMethodChanged(CurrentInputType);
	OnButtonInputMethodChanged.Broadcast(this, CurrentInputType);

	if (TriggeringBindingHandle.IsValid())
	{
		TriggeringBindingHandle.ResetHold();
	}
}

void UGenericButtonWidget::NativeOnButtonStyleChanged()
{
	HandleOnButtonStyleChanged();
	OnButtonStyleChanged.Broadcast(this);
}

/* ==================== Layout ==================== */

void UGenericButtonWidget::SetMinDimensions(int32 InMinWidth, int32 InMinHeight)
{
	MinWidth = InMinWidth;
	MinHeight = InMinHeight;

	RefreshDimensions();
}

void UGenericButtonWidget::RefreshDimensions() const
{
	if (RootButton.IsValid())
	{
		const UCommonButtonStyle* StyleCDO = GetStyleCDO();
		RootButton->SetMinDesiredWidth(FMath::Max(MinWidth, StyleCDO ? StyleCDO->MinWidth : 0));
		RootButton->SetMinDesiredHeight(FMath::Max(MinHeight, StyleCDO ? StyleCDO->MinHeight : 0));
	}
}

/* ==================== Style ==================== */

void UGenericButtonWidget::SetStyle(TSubclassOf<UCommonButtonStyle> InStyle)
{
	if (InStyle && StyleClass != InStyle)
	{
		StyleClass = InStyle;
		BuildStyles();
	}
}

UCommonButtonStyle* UGenericButtonWidget::GetStyle() const
{
	return const_cast<UCommonButtonStyle*>(GetStyleCDO());
}

void UGenericButtonWidget::SetHideInputAction(bool bInHideInputAction)
{
	bHideInputAction = bInHideInputAction;

	UpdateInputActionWidgetVisibility();
}

void UGenericButtonWidget::GetCurrentButtonPadding(FMargin& OutButtonPadding) const
{
	if (const UCommonButtonStyle* CommonButtonStyle = GetStyleCDO())
	{
		CommonButtonStyle->GetButtonPadding(OutButtonPadding);
	}
}

void UGenericButtonWidget::GetCurrentCustomPadding(FMargin& OutCustomPadding) const
{
	if (const UCommonButtonStyle* CommonButtonStyle = GetStyleCDO())
	{
		CommonButtonStyle->GetCustomPadding(OutCustomPadding);
	}
}

TSubclassOf<UCommonTextStyle> UGenericButtonWidget::GetCurrentTextStyleClass() const
{
	if (const UCommonTextStyle* CurrentTextStyle = GetCurrentTextStyle())
	{
		return CurrentTextStyle->GetClass();
	}
	return nullptr;
}

UCommonTextStyle* UGenericButtonWidget::GetCurrentTextStyle() const
{
	if (const UCommonButtonStyle* CommonButtonStyle = GetStyleCDO())
	{
		UCommonTextStyle* CurrentTextStyle = nullptr;
		if (!bButtonEnabled)
		{
			CurrentTextStyle = CommonButtonStyle->GetDisabledTextStyle();
		}
		else if (bSelected)
		{
			if (IsHovered())
			{
				CurrentTextStyle = CommonButtonStyle->GetSelectedHoveredTextStyle();
			}
			if (CurrentTextStyle == nullptr)
			{
				CurrentTextStyle = CommonButtonStyle->GetSelectedTextStyle();
			}
		}

		if (CurrentTextStyle == nullptr)
		{
			if (IsHovered())
			{
				CurrentTextStyle = CommonButtonStyle->GetNormalHoveredTextStyle();
			}
			if (CurrentTextStyle == nullptr)
			{
				CurrentTextStyle = CommonButtonStyle->GetNormalTextStyle();
			}
		}
		return CurrentTextStyle;
	}
	return nullptr;
}

UMaterialInstanceDynamic* UGenericButtonWidget::GetSingleMaterialStyleMID() const
{
	return SingleMaterialStyleMID;
}

const UCommonButtonStyle* UGenericButtonWidget::GetStyleCDO() const
{
	if (StyleClass)
	{
		if (const UCommonButtonStyle* CommonButtonStyle = Cast<UCommonButtonStyle>(StyleClass->ClassDefaultObject))
		{
			return CommonButtonStyle;
		}
	}
	return nullptr;
}

void UGenericButtonWidget::BuildStyles()
{
	if (const UCommonButtonStyle* CommonButtonStyle = GetStyleCDO())
	{
		const FMargin& ButtonPadding = CommonButtonStyle->ButtonPadding;
		const FSlateBrush& DisabledBrush = CommonButtonStyle->Disabled;

		FSlateBrush DynamicSingleMaterialBrush;
		if (CommonButtonStyle->bSingleMaterial)
		{
			DynamicSingleMaterialBrush = CommonButtonStyle->SingleMaterialBrush;

			// Create dynamic instance of material if possible.
			UMaterialInterface* const BaseMaterial = Cast<UMaterialInterface>(DynamicSingleMaterialBrush.GetResourceObject());
			SingleMaterialStyleMID = BaseMaterial ? UMaterialInstanceDynamic::Create(BaseMaterial, this) : nullptr;
			if (SingleMaterialStyleMID)
			{
				DynamicSingleMaterialBrush.SetResourceObject(SingleMaterialStyleMID);
			}
		}
		else
		{
			SingleMaterialStyleMID = nullptr;
		}
		const bool bHasPressedSlateSoundOverride = PressedSlateSoundOverride.GetResourceObject() != nullptr;
		const bool bHasHoveredSlateSoundOverride = HoveredSlateSoundOverride.GetResourceObject() != nullptr;

		NormalStyle.Normal = CommonButtonStyle->bSingleMaterial ? DynamicSingleMaterialBrush : CommonButtonStyle->NormalBase;
		NormalStyle.Hovered = CommonButtonStyle->bSingleMaterial ? DynamicSingleMaterialBrush : CommonButtonStyle->NormalHovered;
		NormalStyle.Pressed = CommonButtonStyle->bSingleMaterial ? DynamicSingleMaterialBrush : CommonButtonStyle->NormalPressed;
		NormalStyle.Disabled = CommonButtonStyle->bSingleMaterial ? DynamicSingleMaterialBrush : DisabledBrush;
		NormalStyle.NormalPadding = ButtonPadding;
		NormalStyle.PressedPadding = ButtonPadding;

		// Sets the sound overrides for the Normal state
		NormalStyle.PressedSlateSound = bHasPressedSlateSoundOverride ? PressedSlateSoundOverride : CommonButtonStyle->PressedSlateSound;
		NormalStyle.HoveredSlateSound = bHasHoveredSlateSoundOverride ? HoveredSlateSoundOverride : CommonButtonStyle->HoveredSlateSound;

		SelectedStyle.Normal = CommonButtonStyle->bSingleMaterial ? DynamicSingleMaterialBrush : CommonButtonStyle->SelectedBase;
		SelectedStyle.Hovered = CommonButtonStyle->bSingleMaterial ? DynamicSingleMaterialBrush : CommonButtonStyle->SelectedHovered;
		SelectedStyle.Pressed = CommonButtonStyle->bSingleMaterial ? DynamicSingleMaterialBrush : CommonButtonStyle->SelectedPressed;
		SelectedStyle.Disabled = CommonButtonStyle->bSingleMaterial ? DynamicSingleMaterialBrush : DisabledBrush;
		SelectedStyle.NormalPadding = ButtonPadding;
		SelectedStyle.PressedPadding = ButtonPadding;

		DisabledStyle = NormalStyle;

		/**
		 * Selected State Sound overrides
		 * If there is no Selected state sound override, the Normal state's sound will be used.
		 * This sound may come from either the button style or the sound override in Blueprints.
		 */
		if (SelectedPressedSlateSoundOverride.GetResourceObject())
		{
			SelectedStyle.PressedSlateSound = SelectedPressedSlateSoundOverride;
		}
		else
		{
			SelectedStyle.PressedSlateSound =
				bHasPressedSlateSoundOverride || !CommonButtonStyle->SelectedPressedSlateSound
					? NormalStyle.PressedSlateSound
					: CommonButtonStyle->SelectedPressedSlateSound.Sound;
		}

		if (SelectedHoveredSlateSoundOverride.GetResourceObject())
		{
			SelectedStyle.HoveredSlateSound = SelectedHoveredSlateSoundOverride;
		}
		else
		{
			SelectedStyle.HoveredSlateSound =
				bHasHoveredSlateSoundOverride || !CommonButtonStyle->SelectedHoveredSlateSound
					? NormalStyle.HoveredSlateSound
					: CommonButtonStyle->SelectedHoveredSlateSound.Sound;
		}

		// Locked State Sound overrides
		LockedStyle = NormalStyle;
		if (CommonButtonStyle->LockedPressedSlateSound || LockedPressedSlateSoundOverride.GetResourceObject())
		{
			LockedStyle.PressedSlateSound =
				LockedPressedSlateSoundOverride.GetResourceObject()
					? LockedPressedSlateSoundOverride
					: CommonButtonStyle->LockedPressedSlateSound.Sound;
		}
		if (CommonButtonStyle->LockedHoveredSlateSound || LockedHoveredSlateSoundOverride.GetResourceObject())
		{
			LockedStyle.HoveredSlateSound =
				LockedHoveredSlateSoundOverride.GetResourceObject()
					? LockedHoveredSlateSoundOverride
					: CommonButtonStyle->LockedHoveredSlateSound.Sound;
		}

		SetButtonStyle();

		RefreshDimensions();
	}
}

void UGenericButtonWidget::SetButtonStyle()
{
	if (UButton* ButtonPtr = RootButton.Get())
	{
		const FButtonStyle* UseStyle;
		if (bLocked)
		{
			UseStyle = &LockedStyle;
		}
		else if (bSelected)
		{
			UseStyle = &SelectedStyle;
		}
		else if (bButtonEnabled)
		{
			UseStyle = &NormalStyle;
		}
		else
		{
			UseStyle = &DisabledStyle;
		}
		ButtonPtr->SetStyle(*UseStyle);
		NativeOnButtonStyleChanged();
	}
}

/* ==================== Sound ==================== */

void UGenericButtonWidget::SetPressedSoundOverride(USoundBase* Sound)
{
	if (PressedSlateSoundOverride.GetResourceObject() != Sound)
	{
		PressedSlateSoundOverride.SetResourceObject(Sound);
		BuildStyles();
	}
}

void UGenericButtonWidget::SetHoveredSoundOverride(USoundBase* Sound)
{
	if (HoveredSlateSoundOverride.GetResourceObject() != Sound)
	{
		HoveredSlateSoundOverride.SetResourceObject(Sound);
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

void UGenericButtonWidget::SetSelectedHoveredSoundOverride(USoundBase* Sound)
{
	if (SelectedHoveredSlateSoundOverride.GetResourceObject() != Sound)
	{
		SelectedHoveredSlateSoundOverride.SetResourceObject(Sound);
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

void UGenericButtonWidget::SetLockedHoveredSoundOverride(USoundBase* Sound)
{
	if (LockedHoveredSlateSoundOverride.GetResourceObject() != Sound)
	{
		LockedHoveredSlateSoundOverride.SetResourceObject(Sound);
		BuildStyles();
	}
}

/* ==================== Locked ==================== */

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

/* ==================== Selection ==================== */

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

	UpdateInputActionWidgetVisibility();
}

void UGenericButtonWidget::SetShouldSelectUponReceivingFocus(bool bInShouldSelectUponReceivingFocus)
{
	if (ensure(bSelectable || !bInShouldSelectUponReceivingFocus))
	{
		bShouldSelectUponReceivingFocus = bInShouldSelectUponReceivingFocus;
	}
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

void UGenericButtonWidget::ClearSelection()
{
	SetSelectedInternal(false, false);
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
			FSlateApplication::Get().PlaySound(NormalStyle.PressedSlateSound);
		}
	}
	else
	{
		// Once deselected, restore the root button interactivity to the desired state
		RootButton->SetInteractionEnabled(bInteractionEnabled);

		NativeOnDeselected();
	}

	UpdateInputActionWidgetVisibility();

	if (bValueChanged)
	{
		BroadcastBinaryPostStateChange(UWidgetSelectedStateRegistration::Bit, bSelected);
	}
}

/* ==================== Hold ==================== */

void UGenericButtonWidget::HoldReset()
{
	if (HoldTickerHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(HoldTickerHandle);
		HoldTickerHandle = nullptr;
	}
	if (HoldRollbackTickerHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(HoldRollbackTickerHandle);
		HoldRollbackTickerHandle = nullptr;
	}
	CurrentHoldTime = 0.0f;
}

void UGenericButtonWidget::UpdateHoldData(ECommonInputType CurrentInputType)
{
	if (HoldData && bRequiresHold)
	{
		if (const UCommonUIHoldData* CommonUIHoldBehaviorValues = HoldData.GetDefaultObject())
		{
			switch (CurrentInputType)
			{
			case ECommonInputType::MouseAndKeyboard:
				HoldTime = CommonUIHoldBehaviorValues->KeyboardAndMouse.HoldTime;
				HoldRollbackTime = CommonUIHoldBehaviorValues->KeyboardAndMouse.HoldRollbackTime;
				break;
			case ECommonInputType::Gamepad:
				HoldTime = CommonUIHoldBehaviorValues->Gamepad.HoldTime;
				HoldRollbackTime = CommonUIHoldBehaviorValues->Gamepad.HoldRollbackTime;
				break;
			case ECommonInputType::Touch:
				HoldTime = CommonUIHoldBehaviorValues->Touch.HoldTime;
				HoldRollbackTime = CommonUIHoldBehaviorValues->Touch.HoldRollbackTime;
				break;
			default:
				break;
			}
		}
	}
}

bool UGenericButtonWidget::NativeOnHoldProgress(float DeltaTime)
{
	if (HoldTime > UE_SMALL_NUMBER)
	{
		CurrentHoldTime += FMath::Clamp(DeltaTime, 0.f, HoldTime);
		const float HeldPercent = FMath::Clamp(CurrentHoldTime / HoldTime, 0.f, 1.f);
		NativeOnHoldActionProgressed(HeldPercent);
		if (HeldPercent >= 1.f)
		{
			NativeOnHoldActionCompleted();
			HandleTriggeringActionCommited();
			HoldReset();
			return false;
		}

		return true;
	}
	HoldReset();

	return false;
}

bool UGenericButtonWidget::NativeOnHoldProgressRollback(float DeltaTime)
{
	if (HoldTime > UE_SMALL_NUMBER && HoldRollbackTime > UE_SMALL_NUMBER)
	{
		const float HoldRollbackMultiplier = HoldTime / HoldRollbackTime;
		CurrentHoldTime = FMath::Clamp(CurrentHoldTime - (DeltaTime * HoldRollbackMultiplier), 0.f, HoldRollbackTime);
		const float HoldRollbackPercent = FMath::Clamp(CurrentHoldTime / HoldTime, 0.f, 1.f);
		NativeOnHoldActionProgressed(HoldRollbackPercent);
		if (HoldRollbackPercent <= 0.f)
		{
			FTSTicker::GetCoreTicker().RemoveTicker(HoldRollbackTickerHandle);
			HoldRollbackTickerHandle = nullptr;

			return false;
		}

		return true;
	}
	HoldReset();

	return false;
}

void UGenericButtonWidget::NativeOnHoldActionProgressed(float HoldPercent)
{
	if (InputActionWidget)
	{
		InputActionWidget->OnActionProgress(HoldPercent);
	}
	OnHoldActionProgress(HoldPercent);
}

void UGenericButtonWidget::NativeOnHoldActionCompleted()
{
	if (InputActionWidget)
	{
		InputActionWidget->OnActionComplete();
	}
	OnHoldActionCompleted();
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

void UGenericButtonWidget::SetShouldUseFallbackDefaultInputAction(bool bInShouldUseFallbackDefaultInputAction)
{
	bShouldUseFallbackDefaultInputAction = bInShouldUseFallbackDefaultInputAction;

	UpdateInputActionWidget();
}

bool UGenericButtonWidget::GetInputAction(FDataTableRowHandle& InputActionRow) const
{
	const bool bBothActionsSet = !TriggeringInputAction.IsNull() && !TriggeredInputAction.IsNull();
	const bool bNoActionSet = TriggeringInputAction.IsNull() && TriggeredInputAction.IsNull();

	if (bBothActionsSet || bNoActionSet)
	{
		return false;
	}

	if (!TriggeringInputAction.IsNull())
	{
		InputActionRow = TriggeringInputAction;
		return true;
	}
	else
	{
		InputActionRow = TriggeredInputAction;
		return true;
	}
}

void UGenericButtonWidget::SetTriggeringInputAction(const FDataTableRowHandle& InputActionRow)
{
	if (TriggeringInputAction != InputActionRow)
	{
		UnbindTriggeringInputActionToClick();

		TriggeringInputAction = InputActionRow;

		if (!IsDesignTime())
		{
			BindTriggeringInputActionToClick();
		}

		// Update the Input action widget whenever the triggering input action changes
		UpdateInputActionWidget();

		OnTriggeringInputActionChanged(InputActionRow);
	}
}

void UGenericButtonWidget::SetTriggeredInputAction(const FDataTableRowHandle& InputActionRow)
{
	if (ensure(TriggeringInputAction.IsNull()))
	{
		TriggeredInputAction = InputActionRow;
		UpdateInputActionWidget();

		OnTriggeredInputActionChanged(InputActionRow);
	}
}

UInputAction* UGenericButtonWidget::GetTriggeringEnhancedInputAction() const
{
	return TriggeringEnhancedInputAction;
}

void UGenericButtonWidget::SetTriggeringEnhancedInputAction(UInputAction* InInputAction)
{
	if (CommonUI::IsEnhancedInputSupportEnabled() && TriggeringEnhancedInputAction != InInputAction)
	{
		UnbindTriggeringInputActionToClick();

		TriggeringEnhancedInputAction = InInputAction;

		if (!IsDesignTime())
		{
			BindTriggeringInputActionToClick();
		}

		// Update the Input action widget whenever the triggering input action changes
		UpdateInputActionWidget();

		OnTriggeringEnhancedInputActionChanged(InInputAction);
	}
}

void UGenericButtonWidget::BindInputMethodChangedDelegate()
{
	if (UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem())
	{
		CommonInputSubsystem->OnInputMethodChangedNative.AddUObject(this, &UGenericButtonWidget::NativeInputMethodChanged);
		UpdateHoldData(CommonInputSubsystem->GetDefaultInputType());
	}
}

void UGenericButtonWidget::UnbindInputMethodChangedDelegate()
{
	if (UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem())
	{
		CommonInputSubsystem->OnInputMethodChangedNative.RemoveAll(this);
	}
}

void UGenericButtonWidget::BindTriggeringInputActionToClick()
{
	if (CommonUI::IsEnhancedInputSupportEnabled() && TriggeringEnhancedInputAction)
	{
		FBindUIActionArgs BindArgs(TriggeringEnhancedInputAction, false, FSimpleDelegate::CreateUObject(this, &UGenericButtonWidget::HandleTriggeringActionCommited));
		BindArgs.OnHoldActionProgressed.BindUObject(this, &UGenericButtonWidget::NativeOnHoldActionProgressed);
		BindArgs.bIsPersistent = bIsPersistentBinding;

		BindArgs.InputMode = InputModeOverride;

		TriggeringBindingHandle = RegisterUIActionBinding(BindArgs);

		return;
	}

	if (TriggeringInputAction.IsNull() || !TriggeredInputAction.IsNull())
	{
		return;
	}

	if (!TriggeringBindingHandle.IsValid())
	{
		FBindUIActionArgs BindArgs(TriggeringInputAction, false, FSimpleDelegate::CreateUObject(this, &UGenericButtonWidget::HandleTriggeringActionCommited));
		BindArgs.OnHoldActionProgressed.BindUObject(this, &UGenericButtonWidget::NativeOnHoldActionProgressed);
		BindArgs.OnHoldActionPressed.BindUObject(this, &UGenericButtonWidget::NativeOnPressed);
		BindArgs.OnHoldActionReleased.BindUObject(this, &UGenericButtonWidget::NativeOnReleased);
		BindArgs.bIsPersistent = bIsPersistentBinding;
		BindArgs.bForceHold = bRequiresHold;

		BindArgs.InputMode = InputModeOverride;

		TriggeringBindingHandle = RegisterUIActionBinding(BindArgs);
	}
}

void UGenericButtonWidget::UnbindTriggeringInputActionToClick()
{
	if (CommonUI::IsEnhancedInputSupportEnabled() && TriggeringEnhancedInputAction)
	{
		TriggeringBindingHandle.Unregister();

		return;
	}

	if (TriggeringInputAction.IsNull() || !TriggeredInputAction.IsNull())
	{
		return;
	}

	if (TriggeringBindingHandle.IsValid())
	{
		TriggeringBindingHandle.Unregister();
	}

	CurrentHoldTime = 0.f;
}

void UGenericButtonWidget::HandleTriggeringActionCommited()
{
	// Because this path doesn't go through SButton::Press(), the sound needs to be played from here.
	FSlateApplication::Get().PlaySound(NormalStyle.PressedSlateSound);
	HandleButtonClicked();
}

void UGenericButtonWidget::UpdateInputActionWidget()
{
	// Update the input action state of the input action widget contextually based on the current state of the button
	if (GetGameInstance() && InputActionWidget)
	{
		const bool bIsEnhancedInputSupportEnabled = CommonUI::IsEnhancedInputSupportEnabled();

		// Prefer visualizing the triggering enhanced input action before all else
		if (bIsEnhancedInputSupportEnabled && TriggeringEnhancedInputAction)
		{
			InputActionWidget->SetEnhancedInputAction(TriggeringEnhancedInputAction);
		}
		// Prefer visualizing the triggering input action next
		else if (!TriggeringInputAction.IsNull())
		{
			InputActionWidget->SetInputAction(TriggeringInputAction);
		}
		// Fallback to visualizing the triggered input action, if it's available
		else if (!TriggeredInputAction.IsNull())
		{
			InputActionWidget->SetInputAction(TriggeredInputAction);
		}
		// Visualize the default click action when neither input action is bound and when the widget is enabled and hovered
		else if (bShouldUseFallbackDefaultInputAction && bButtonEnabled)
		{
			FDataTableRowHandle HoverStateHandle;
			UInputAction* HoverEnhancedInputAction = nullptr;
			if (IsHovered())
			{
				if (bIsEnhancedInputSupportEnabled)
				{
					HoverEnhancedInputAction = ICommonInputModule::GetSettings().GetEnhancedInputClickAction();
				}
				else
				{
					HoverStateHandle = ICommonInputModule::GetSettings().GetDefaultClickAction();
				}
			}

			if (bIsEnhancedInputSupportEnabled)
			{
				InputActionWidget->SetEnhancedInputAction(HoverEnhancedInputAction);
			}
			else
			{
				InputActionWidget->SetInputAction(HoverStateHandle);
			}
		}
		else
		{
			if (bIsEnhancedInputSupportEnabled)
			{
				InputActionWidget->SetEnhancedInputAction(nullptr);
			}

			const FDataTableRowHandle EmptyStateHandle;
			InputActionWidget->SetInputAction(EmptyStateHandle);
		}

		UpdateInputActionWidgetVisibility();
	}
}

void UGenericButtonWidget::UpdateInputActionWidgetVisibility() const
{
	if (InputActionWidget)
	{
		bool bHidden = false;

		const UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem();

		if (bHideInputAction)
		{
			bHidden = true;
		}
		else if (CommonInputSubsystem && bHideInputActionWithKeyboard && CommonInputSubsystem->GetCurrentInputType() != ECommonInputType::Gamepad)
		{
			bHidden = true;
		}
		else if (bSelected)
		{
			if (!bToggleable)
			{
				if (!bDisplayInputActionWhenNotInteractable && !bInteractableWhenSelected)
				{
					bHidden = true;
				}
			}
		}
		else
		{
			if (!bDisplayInputActionWhenNotInteractable && !bInteractionEnabled)
			{
				bHidden = true;
			}
		}

		InputActionWidget->SetHidden(bHidden);
	}
}

/* ==================== Interaction ==================== */

void UGenericButtonWidget::DisableButtonWithReason(const FText& DisabledReason)
{
	DisabledTooltipText = DisabledReason;
	SetIsEnabled(false);
}

bool UGenericButtonWidget::IsInteractionEnabled() const
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

		if (bApplyAlphaOnDisable)
		{
			FLinearColor ButtonColor = RootButton->GetColorAndOpacity();
			ButtonColor.A = 1.f;
			RootButton->SetColorAndOpacity(ButtonColor);
		}
	}
	else
	{
		RootButton->SetInteractionEnabled(false);

		if (bApplyAlphaOnDisable)
		{
			FLinearColor ButtonColor = RootButton->GetColorAndOpacity();
			ButtonColor.A = 0.5f;
			RootButton->SetColorAndOpacity(ButtonColor);
		}
	}

	UpdateInputActionWidgetVisibility();

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

		if (InputActionWidget)
		{
			UpdateInputActionWidget();
			InputActionWidget->SetIsEnabled(bButtonEnabled);
		}
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

		if (InputActionWidget)
		{
			UpdateInputActionWidget();
			InputActionWidget->SetIsEnabled(bButtonEnabled);
		}
	}
}
