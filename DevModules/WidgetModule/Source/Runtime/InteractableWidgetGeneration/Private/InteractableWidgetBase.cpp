// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractableWidgetBase.h"

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

#if WITH_EDITOR
#include "CommonUIEditorSettings.h"
#endif

/* ==================== UInteractableWidgetBase ==================== */

UInteractableWidgetBase::UInteractableWidgetBase(const FObjectInitializer& ObjectInitializer)
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
	SetIsFocusable(true);

	if (const TSubclassOf<UCommonButtonStyle> TransparentStyleClass = LoadClass<UCommonButtonStyle>(nullptr, TEXT("/Script/Engine.Blueprint'/WidgetModule/ButtonStyle/CBS_Transparent.CBS_Transparent_C'")))
	{
		StyleClass = TransparentStyleClass;
	}
}

/* ==================== UUserWidget ==================== */

bool UInteractableWidgetBase::Initialize()
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

		RootButton->OnClicked.AddUniqueDynamic(this, &UInteractableWidgetBase::HandleButtonClicked);
		RootButton->OnDoubleClicked.AddUniqueDynamic(this, &UInteractableWidgetBase::HandleButtonDoubleClicked);
		RootButton->OnReceivedFocus.AddUniqueDynamic(this, &UInteractableWidgetBase::HandleFocusReceived);
		RootButton->OnLostFocus.AddUniqueDynamic(this, &UInteractableWidgetBase::HandleFocusLost);
		RootButton->OnPressed.AddUniqueDynamic(this, &UInteractableWidgetBase::HandleButtonPressed);
		RootButton->OnReleased.AddUniqueDynamic(this, &UInteractableWidgetBase::HandleButtonReleased);
	}

	return bInitializedThisCall;
}

void UInteractableWidgetBase::NativeConstruct()
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

void UInteractableWidgetBase::NativeDestruct()
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

bool UInteractableWidgetBase::NativeIsInteractable() const
{
	// If it's enabled, it's "interactable" from a UMG perspective. 
	// For now this is how we generate friction on the analog cursor, which we still want for disabled buttons since they have tooltips.
	return GetIsEnabled();
}

void UInteractableWidgetBase::SetIsEnabled(bool bInIsEnabled)
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

bool UInteractableWidgetBase::IsHovered() const
{
	return RootButton.IsValid() && RootButton->IsHovered();
}

void UInteractableWidgetBase::OnWidgetRebuilt()
{
	Super::OnWidgetRebuilt();
	// GetCachedWidget()->AddMetadata<FCommonButtonMetaData>(MakeShared<FCommonButtonMetaData>(*this));
}

void UInteractableWidgetBase::PostLoad()
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

void UInteractableWidgetBase::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	RefreshDimensions();
	BuildStyles();
}

FReply UInteractableWidgetBase::NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent)
{
	FReply Reply = Super::NativeOnFocusReceived(InGeometry, InFocusEvent);

	HandleFocusReceived();

	return Reply;
}

void UInteractableWidgetBase::NativeOnFocusLost(const FFocusEvent& InFocusEvent)
{
	Super::NativeOnFocusLost(InFocusEvent);

	HandleFocusLost();
}

void UInteractableWidgetBase::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
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

void UInteractableWidgetBase::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
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

void UInteractableWidgetBase::OnCreationFromPalette()
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

UGenericButton* UInteractableWidgetBase::ConstructInternalButton()
{
	return WidgetTree->ConstructWidget<UGenericButton>(UGenericButton::StaticClass(), FName(TEXT("GenericButton")));
}

/* ==================== Event ==================== */

void UInteractableWidgetBase::HandleButtonClicked()
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

void UInteractableWidgetBase::HandleButtonDoubleClicked()
{
	NativeOnDoubleClicked();
}

void UInteractableWidgetBase::HandleFocusReceived()
{
	if (bShouldSelectUponReceivingFocus && !GetIsSelected())
	{
		SetIsSelected(true, false);
	}
	NativeOnFocusReceived();
}

void UInteractableWidgetBase::HandleFocusLost()
{
	NativeOnFocusLost();
}

void UInteractableWidgetBase::HandleButtonPressed()
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
		HoldTickerHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UInteractableWidgetBase::NativeOnHoldProgress));
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

void UInteractableWidgetBase::HandleButtonReleased()
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
			HoldRollbackTickerHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateUObject(this, &UInteractableWidgetBase::NativeOnHoldProgressRollback));

			FTSTicker::GetCoreTicker().RemoveTicker(HoldTickerHandle);
			HoldTickerHandle = nullptr;
		}
	}
}

void UInteractableWidgetBase::NativeOnEnabled()
{
	HandleOnButtonEnabled();
	OnButtonEnabled.Broadcast(this);
	NativeOnButtonStyleChanged();
}

void UInteractableWidgetBase::NativeOnDisabled()
{
	HandleOnButtonDisabled();
	OnButtonDisabled.Broadcast(this);
	NativeOnButtonStyleChanged();
}

void UInteractableWidgetBase::NativeOnPressed()
{
	HoldReset();
	HandleOnButtonPressed();
	OnButtonPressed.Broadcast(this);
	BroadcastBinaryPostStateChange(UWidgetPressedStateRegistration::Bit, true);
}

void UInteractableWidgetBase::NativeOnReleased()
{
	HandleOnButtonReleased();
	OnButtonReleased.Broadcast(this);
	BroadcastBinaryPostStateChange(UWidgetPressedStateRegistration::Bit, false);
}

void UInteractableWidgetBase::NativeOnHovered()
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

void UInteractableWidgetBase::NativeOnUnhovered()
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

void UInteractableWidgetBase::NativeOnClicked()
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

void UInteractableWidgetBase::NativeOnDoubleClicked()
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

void UInteractableWidgetBase::NativeOnSelected()
{
	HandleOnButtonSelectionChanged(true);
	OnButtonSelectionChanged.Broadcast(this, true);
	NativeOnButtonStyleChanged();

	if (SelectedAnimation)
	{
		PlayAnimationForward(SelectedAnimation);
	}
}

void UInteractableWidgetBase::NativeOnDeselected()
{
	HandleOnButtonSelectionChanged(false);
	OnButtonSelectionChanged.Broadcast(this, false);
	NativeOnButtonStyleChanged();

	if (SelectedAnimation)
	{
		PlayAnimationReverse(SelectedAnimation);
	}
}

void UInteractableWidgetBase::NativeOnFocusReceived()
{
	HandleOnButtonFocusReceived();
	OnButtonFocusReceived.Broadcast(this);
}

void UInteractableWidgetBase::NativeOnFocusLost()
{
	HandleOnButtonFocusLost();
	OnButtonFocusLost.Broadcast(this);
}

void UInteractableWidgetBase::NativeOnLockedChanged(bool bIsLocked)
{
	HandleOnButtonLockedChanged(bIsLocked);
	OnButtonLockedChanged.Broadcast(this, bIsLocked);
}

void UInteractableWidgetBase::NativeOnLockClicked()
{
	HandleOnButtonLockClicked();
	OnButtonLockClicked.Broadcast(this);
}

void UInteractableWidgetBase::NativeOnLockDoubleClicked()
{
	HandleOnButtonLockDoubleClicked();
	OnButtonLockDoubleClicked.Broadcast(this);
}

void UInteractableWidgetBase::NativeInputMethodChanged(ECommonInputType CurrentInputType)
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

void UInteractableWidgetBase::NativeOnButtonStyleChanged()
{
	HandleOnButtonStyleChanged();
	OnButtonStyleChanged.Broadcast(this);
}

/* ==================== Layout ==================== */

void UInteractableWidgetBase::SetMinDimensions(int32 InMinWidth, int32 InMinHeight)
{
	MinWidth = InMinWidth;
	MinHeight = InMinHeight;

	RefreshDimensions();
}

void UInteractableWidgetBase::RefreshDimensions() const
{
	if (RootButton.IsValid())
	{
		const UCommonButtonStyle* const StyleCDO = GetStyleCDO();
		RootButton->SetMinDesiredWidth(FMath::Max(MinWidth, StyleCDO ? StyleCDO->MinWidth : 0));
		RootButton->SetMinDesiredHeight(FMath::Max(MinHeight, StyleCDO ? StyleCDO->MinHeight : 0));
	}
}

/* ==================== Style ==================== */

void UInteractableWidgetBase::SetStyle(TSubclassOf<UCommonButtonStyle> InStyle)
{
	if (InStyle && StyleClass != InStyle)
	{
		StyleClass = InStyle;
		BuildStyles();
	}
}

UCommonButtonStyle* UInteractableWidgetBase::GetStyle() const
{
	return const_cast<UCommonButtonStyle*>(GetStyleCDO());
}

void UInteractableWidgetBase::SetHideInputAction(bool bInHideInputAction)
{
	bHideInputAction = bInHideInputAction;

	UpdateInputActionWidgetVisibility();
}

void UInteractableWidgetBase::GetCurrentButtonPadding(FMargin& OutButtonPadding) const
{
	if (const UCommonButtonStyle* CommonButtonStyle = GetStyleCDO())
	{
		CommonButtonStyle->GetButtonPadding(OutButtonPadding);
	}
}

void UInteractableWidgetBase::GetCurrentCustomPadding(FMargin& OutCustomPadding) const
{
	if (const UCommonButtonStyle* CommonButtonStyle = GetStyleCDO())
	{
		CommonButtonStyle->GetCustomPadding(OutCustomPadding);
	}
}

TSubclassOf<UCommonTextStyle> UInteractableWidgetBase::GetCurrentTextStyleClass() const
{
	if (const UCommonTextStyle* CurrentTextStyle = GetCurrentTextStyle())
	{
		return CurrentTextStyle->GetClass();
	}
	return nullptr;
}

UCommonTextStyle* UInteractableWidgetBase::GetCurrentTextStyle() const
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

UMaterialInstanceDynamic* UInteractableWidgetBase::GetSingleMaterialStyleMID() const
{
	return SingleMaterialStyleMID;
}

const UCommonButtonStyle* UInteractableWidgetBase::GetStyleCDO() const
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

void UInteractableWidgetBase::BuildStyles()
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

void UInteractableWidgetBase::SetButtonStyle()
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

void UInteractableWidgetBase::SetPressedSoundOverride(USoundBase* Sound)
{
	if (PressedSlateSoundOverride.GetResourceObject() != Sound)
	{
		PressedSlateSoundOverride.SetResourceObject(Sound);
		BuildStyles();
	}
}

void UInteractableWidgetBase::SetHoveredSoundOverride(USoundBase* Sound)
{
	if (HoveredSlateSoundOverride.GetResourceObject() != Sound)
	{
		HoveredSlateSoundOverride.SetResourceObject(Sound);
		BuildStyles();
	}
}

void UInteractableWidgetBase::SetSelectedPressedSoundOverride(USoundBase* Sound)
{
	if (SelectedPressedSlateSoundOverride.GetResourceObject() != Sound)
	{
		SelectedPressedSlateSoundOverride.SetResourceObject(Sound);
		BuildStyles();
	}
}

void UInteractableWidgetBase::SetSelectedHoveredSoundOverride(USoundBase* Sound)
{
	if (SelectedHoveredSlateSoundOverride.GetResourceObject() != Sound)
	{
		SelectedHoveredSlateSoundOverride.SetResourceObject(Sound);
		BuildStyles();
	}
}

void UInteractableWidgetBase::SetLockedPressedSoundOverride(USoundBase* Sound)
{
	if (LockedPressedSlateSoundOverride.GetResourceObject() != Sound)
	{
		LockedPressedSlateSoundOverride.SetResourceObject(Sound);
		BuildStyles();
	}
}

void UInteractableWidgetBase::SetLockedHoveredSoundOverride(USoundBase* Sound)
{
	if (LockedHoveredSlateSoundOverride.GetResourceObject() != Sound)
	{
		LockedHoveredSlateSoundOverride.SetResourceObject(Sound);
		BuildStyles();
	}
}

/* ==================== Locked ==================== */

bool UInteractableWidgetBase::GetIsLocked() const
{
	return bLocked;
}

void UInteractableWidgetBase::SetIsLocked(bool bInIsLocked)
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

void UInteractableWidgetBase::SetIsSelectable(bool bInIsSelectable)
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

void UInteractableWidgetBase::SetIsToggleable(bool bInIsToggleable)
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

void UInteractableWidgetBase::SetShouldSelectUponReceivingFocus(bool bInShouldSelectUponReceivingFocus)
{
	if (ensure(bSelectable || !bInShouldSelectUponReceivingFocus))
	{
		bShouldSelectUponReceivingFocus = bInShouldSelectUponReceivingFocus;
	}
}

void UInteractableWidgetBase::SetIsInteractableWhenSelected(bool bInInteractableWhenSelected)
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

bool UInteractableWidgetBase::GetIsSelected() const
{
	return bSelected;
}

void UInteractableWidgetBase::SetIsSelected(bool InSelected, bool bGiveClickFeedback)
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

void UInteractableWidgetBase::ClearSelection()
{
	SetSelectedInternal(false, false);
}

void UInteractableWidgetBase::SetSelectedInternal(bool bInSelected, bool bGiveClickFeedback /*= true*/, bool bBroadcast /*= true*/)
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

void UInteractableWidgetBase::HoldReset()
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

void UInteractableWidgetBase::UpdateHoldData(ECommonInputType CurrentInputType)
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

bool UInteractableWidgetBase::NativeOnHoldProgress(float DeltaTime)
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

bool UInteractableWidgetBase::NativeOnHoldProgressRollback(float DeltaTime)
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

void UInteractableWidgetBase::NativeOnHoldActionProgressed(float HoldPercent)
{
	if (InputActionWidget)
	{
		InputActionWidget->OnActionProgress(HoldPercent);
	}
	OnHoldActionProgress(HoldPercent);
}

void UInteractableWidgetBase::NativeOnHoldActionCompleted()
{
	if (InputActionWidget)
	{
		InputActionWidget->OnActionComplete();
	}
	OnHoldActionCompleted();
}

/* ==================== Input ==================== */

void UInteractableWidgetBase::SetClickMethod(EButtonClickMethod::Type InClickMethod)
{
	ClickMethod = InClickMethod;
	if (RootButton.IsValid())
	{
		RootButton->SetClickMethod(ClickMethod);
	}
}

void UInteractableWidgetBase::SetTouchMethod(EButtonTouchMethod::Type InTouchMethod)
{
	TouchMethod = InTouchMethod;
	if (RootButton.IsValid())
	{
		RootButton->SetTouchMethod(InTouchMethod);
	}
}

void UInteractableWidgetBase::SetPressMethod(EButtonPressMethod::Type InPressMethod)
{
	PressMethod = InPressMethod;
	if (RootButton.IsValid())
	{
		RootButton->SetPressMethod(InPressMethod);
	}
}

void UInteractableWidgetBase::SetShouldUseFallbackDefaultInputAction(bool bInShouldUseFallbackDefaultInputAction)
{
	bShouldUseFallbackDefaultInputAction = bInShouldUseFallbackDefaultInputAction;

	UpdateInputActionWidget();
}

bool UInteractableWidgetBase::GetInputAction(FDataTableRowHandle& InputActionRow) const
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

void UInteractableWidgetBase::SetTriggeringInputAction(const FDataTableRowHandle& InputActionRow)
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

void UInteractableWidgetBase::SetTriggeredInputAction(const FDataTableRowHandle& InputActionRow)
{
	if (ensure(TriggeringInputAction.IsNull()))
	{
		TriggeredInputAction = InputActionRow;
		UpdateInputActionWidget();

		OnTriggeredInputActionChanged(InputActionRow);
	}
}

UInputAction* UInteractableWidgetBase::GetTriggeringEnhancedInputAction() const
{
	return TriggeringEnhancedInputAction;
}

void UInteractableWidgetBase::SetTriggeringEnhancedInputAction(UInputAction* InInputAction)
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

void UInteractableWidgetBase::BindInputMethodChangedDelegate()
{
	if (UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem())
	{
		CommonInputSubsystem->OnInputMethodChangedNative.AddUObject(this, &UInteractableWidgetBase::NativeInputMethodChanged);
		UpdateHoldData(CommonInputSubsystem->GetDefaultInputType());
	}
}

void UInteractableWidgetBase::UnbindInputMethodChangedDelegate()
{
	if (UCommonInputSubsystem* CommonInputSubsystem = GetInputSubsystem())
	{
		CommonInputSubsystem->OnInputMethodChangedNative.RemoveAll(this);
	}
}

void UInteractableWidgetBase::BindTriggeringInputActionToClick()
{
	if (CommonUI::IsEnhancedInputSupportEnabled() && TriggeringEnhancedInputAction)
	{
		FBindUIActionArgs BindArgs(TriggeringEnhancedInputAction, false, FSimpleDelegate::CreateUObject(this, &UInteractableWidgetBase::HandleTriggeringActionCommited));
		BindArgs.OnHoldActionProgressed.BindUObject(this, &UInteractableWidgetBase::NativeOnHoldActionProgressed);
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
		FBindUIActionArgs BindArgs(TriggeringInputAction, false, FSimpleDelegate::CreateUObject(this, &UInteractableWidgetBase::HandleTriggeringActionCommited));
		BindArgs.OnHoldActionProgressed.BindUObject(this, &UInteractableWidgetBase::NativeOnHoldActionProgressed);
		BindArgs.OnHoldActionPressed.BindUObject(this, &UInteractableWidgetBase::NativeOnPressed);
		BindArgs.OnHoldActionReleased.BindUObject(this, &UInteractableWidgetBase::NativeOnReleased);
		BindArgs.bIsPersistent = bIsPersistentBinding;
		BindArgs.bForceHold = bRequiresHold;

		BindArgs.InputMode = InputModeOverride;

		TriggeringBindingHandle = RegisterUIActionBinding(BindArgs);
	}
}

void UInteractableWidgetBase::UnbindTriggeringInputActionToClick()
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

void UInteractableWidgetBase::HandleTriggeringActionCommited()
{
	// Because this path doesn't go through SButton::Press(), the sound needs to be played from here.
	FSlateApplication::Get().PlaySound(NormalStyle.PressedSlateSound);
	HandleButtonClicked();
}

void UInteractableWidgetBase::UpdateInputActionWidget()
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

void UInteractableWidgetBase::UpdateInputActionWidgetVisibility() const
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

void UInteractableWidgetBase::DisableButtonWithReason(const FText& DisabledReason)
{
	DisabledTooltipText = DisabledReason;
	SetIsEnabled(false);
}

bool UInteractableWidgetBase::IsInteractionEnabled() const
{
	ESlateVisibility Vis = GetVisibility(); // hidden or collapsed should have 'bInteractionEnabled' set false, but sometimes they don't :(
	return GetIsEnabled() && bButtonEnabled && bInteractionEnabled && (Vis != ESlateVisibility::Collapsed) && (Vis != ESlateVisibility::Hidden);
}

void UInteractableWidgetBase::SetIsInteractionEnabled(bool bInIsInteractionEnabled)
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

void UInteractableWidgetBase::EnableButton()
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

void UInteractableWidgetBase::DisableButton()
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

/* ==================== UInteractableWidgetBase ==================== */

bool UInteractableWidgetBase::GetIsFocusable() const
{
	return IsFocusable();
}

void UInteractableWidgetBase::SetIsFocusable(bool bInIsFocusable)
{
	UUserWidget::SetIsFocusable(bInIsFocusable);

	if (RootButton.IsValid())
	{
		RootButton->SetButtonFocusable(bInIsFocusable);
	}
}

bool UInteractableWidgetBase::IsPressed() const
{
	return RootButton.IsValid() && RootButton->IsPressed();
}
