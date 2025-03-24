// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonInputModeTypes.h"
#include "CommonUITypes.h"
#include "Base/UserWidgetBase.h"
#include "Input/UIActionBindingHandle.h"
#include "InteractableWidgetBase.generated.h"

class UCommonTextStyle;
class UCommonActionWidget;
class UCommonUISubsystemBase;
class UCommonInputSubsystem;
class UInputAction;
class UCommonButtonStyle;
class UCommonUIHoldData;
class UGenericButton;
class UScreenWidgetManager;
class UProcedureProxy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractableWidgetEvent, UInteractableWidgetBase*, Button);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectedStateChangedEvent, UInteractableWidgetBase*, Button, bool, IsSelected);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonLockEvent, UInteractableWidgetBase*, Button, bool, IsLocked);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonInputMethodChangedEvent, UInteractableWidgetBase*, Button, ECommonInputType, CurrentInputType);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonHoldingEvent, UInteractableWidgetBase*, Button, float, Percent);

/**
 * 
 */
UCLASS(Abstract)
class INTERACTABLEWIDGETGENERATION_API UInteractableWidgetBase : public UUserWidgetBase
{
	GENERATED_BODY()

	/* ==================== UInteractableWidgetBase ==================== */
public:
	UInteractableWidgetBase(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual bool NativeIsInteractable() const override;
	virtual void SetIsEnabled(bool bInIsEnabled) override;
	virtual bool IsHovered() const override;

protected:
	virtual void OnWidgetRebuilt() override;
	virtual void PostLoad() override;
	virtual void SynchronizeProperties() override;

	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

#if WITH_EDITOR
	virtual void OnCreationFromPalette() override;
#endif

	virtual UGenericButton* ConstructInternalButton();

private:
	TWeakObjectPtr<class UGenericButton> RootButton;

	/* ==================== Event ==================== */
protected:
	/** Helper function registered to the underlying button when pressed */
	UFUNCTION()
	void HandleButtonPressed();

	/** Helper function registered to the underlying button when released */
	UFUNCTION()
	void HandleButtonReleased();

	/** Handler function registered to the underlying button's click. */
	UFUNCTION()
	void HandleButtonClicked();

	/** Handler function registered to the underlying button's double click. */
	UFUNCTION()
	void HandleButtonDoubleClicked();

	/** Helper function registered to the underlying button receiving focus */
	UFUNCTION()
	virtual void HandleFocusReceived();

	/** Helper function registered to the underlying button losing focus */
	UFUNCTION()
	virtual void HandleFocusLost();

protected:
	virtual void NativeOnEnabled();
	virtual void NativeOnDisabled();
	virtual void NativeOnPressed();
	virtual void NativeOnReleased();
	virtual void NativeOnHovered();
	virtual void NativeOnUnhovered();
	virtual void NativeOnClicked();
	virtual void NativeOnDoubleClicked();
	virtual void NativeOnSelected();
	virtual void NativeOnDeselected();
	virtual void NativeOnFocusReceived();
	virtual void NativeOnFocusLost();
	virtual void NativeOnLockedChanged(bool bIsLocked);
	virtual void NativeOnLockClicked();
	virtual void NativeOnLockDoubleClicked();
	virtual void NativeInputMethodChanged(ECommonInputType CurrentInputType);
	virtual void NativeOnButtonStyleChanged();

public:
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractableWidgetEvent OnButtonEnabled;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractableWidgetEvent OnButtonDisabled;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractableWidgetEvent OnButtonPressed;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractableWidgetEvent OnButtonReleased;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractableWidgetEvent OnButtonHovered;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractableWidgetEvent OnButtonUnhovered;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractableWidgetEvent OnButtonClicked;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractableWidgetEvent OnButtonDoubleClicked;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSelectedStateChangedEvent OnButtonSelectionChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractableWidgetEvent OnButtonFocusReceived;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractableWidgetEvent OnButtonFocusLost;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnButtonLockEvent OnButtonLockedChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractableWidgetEvent OnButtonLockClicked;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractableWidgetEvent OnButtonLockDoubleClicked;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnButtonInputMethodChangedEvent OnButtonInputMethodChanged;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FInteractableWidgetEvent OnButtonStyleChanged;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonEnabled();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonDisabled();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonPressed();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonReleased();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonHovered();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonUnhovered();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonDoubleClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonSelectionChanged(bool IsSelected);

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonFocusReceived();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonFocusLost();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonLockedChanged(bool IsLock);

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonLockClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonLockDoubleClicked();

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonInputMethodChanged(ECommonInputType InInputType);

	UFUNCTION(BlueprintImplementableEvent)
	void HandleOnButtonStyleChanged();

public:
	UPROPERTY(meta=(BindWidgetAnimOptional), Transient)
	TObjectPtr<UWidgetAnimation> HoveredAnimation = nullptr;

	UPROPERTY(meta=(BindWidgetAnimOptional), Transient)
	TObjectPtr<UWidgetAnimation> SelectedAnimation = nullptr;

	/* ==================== Layout ==================== */
public:
	/** The minimum width of the button (only used if greater than the style's minimum) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout", meta = (ClampMin = "0"))
	int32 MinWidth;

	/** The minimum height of the button (only used if greater than the style's minimum) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Layout", meta = (ClampMin = "0"))
	int32 MinHeight;

public:
	/** Sets the minimum dimensions of this button */
	UFUNCTION(BlueprintCallable)
	void SetMinDimensions(int32 InMinWidth, int32 InMinHeight);

protected:
	void RefreshDimensions() const;

	/* ==================== Style ==================== */
public:
	/** References the button style asset that defines a style in multiple sizes */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Style")
	TSubclassOf<UCommonButtonStyle> StyleClass;

	/** Whether to hide the input action widget at all times (useful for textless small buttons) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Style")
	bool bHideInputAction;

	/** The type of mouse action required by the user to trigger the button's 'Click' */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Style")
	uint8 bApplyAlphaOnDisable : 1;

public:
	/** Current button style*/
	UFUNCTION(BlueprintPure)
	UCommonButtonStyle* GetStyle() const;

	/** Sets the style of this button, rebuilds the internal styling */
	UFUNCTION(BlueprintCallable)
	void SetStyle(TSubclassOf<UCommonButtonStyle> InStyle = nullptr);

	UFUNCTION(BlueprintCallable)
	void SetHideInputAction(bool bInHideInputAction);

	/** The current button padding that corresponds to the current size and selection state */
	UFUNCTION(BlueprintCallable)
	void GetCurrentButtonPadding(FMargin& OutButtonPadding) const;

	/** The custom padding that corresponds to the current size and selection state */
	UFUNCTION(BlueprintCallable)
	void GetCurrentCustomPadding(FMargin& OutCustomPadding) const;

	/** The class of the text style that corresponds to the current size and selection state */
	UFUNCTION(BlueprintCallable)
	TSubclassOf<UCommonTextStyle> GetCurrentTextStyleClass() const;

	/** The text style that corresponds to the current size and selection state */
	UFUNCTION(BlueprintCallable)
	UCommonTextStyle* GetCurrentTextStyle() const;

	/** Returns the dynamic instance of the material being used for this button, if it is using a single material style. */
	UFUNCTION(BlueprintPure)
	UMaterialInstanceDynamic* GetSingleMaterialStyleMID() const;

public:
	const UCommonButtonStyle* GetStyleCDO() const;

protected:
	/** Internally managed and applied style to use when not selected */
	UPROPERTY()
	FButtonStyle NormalStyle;

	/** Internally managed and applied style to use when selected */
	UPROPERTY()
	FButtonStyle SelectedStyle;

	/** Internally managed and applied style to use when disabled */
	UPROPERTY()
	FButtonStyle DisabledStyle;

	/** Internally managed and applied style to use when locked */
	UPROPERTY()
	FButtonStyle LockedStyle;

	/** The dynamic material instance of the material set by the single material style, if specified. */
	UPROPERTY(Transient)
	TObjectPtr<UMaterialInstanceDynamic> SingleMaterialStyleMID;

#if WITH_EDITORONLY_DATA
	/** Used to track widgets that were created before changing the default style pointer to null */
	UPROPERTY()
	bool bStyleNoLongerNeedsConversion;
#endif

private:
	void BuildStyles();
	void SetButtonStyle();

	/* ==================== Sound ==================== */
public:
	/**
	 * Optional override for the sound to play when this button is pressed.
	 * Also used for the Selected and Locked Pressed state if their respective overrides are empty.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (DisplayName = "Pressed Sound Override"))
	FSlateSound PressedSlateSoundOverride;

	/**
	 * Optional override for the sound to play when this button is hovered.
	 * Also used for the Selected and Locked Hovered state if their respective overrides are empty.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (DisplayName = "Hovered Sound Override"))
	FSlateSound HoveredSlateSoundOverride;

	/** Optional override for the sound to play when this button is pressed while Selected */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (DisplayName = "Selected Pressed Sound Override"))
	FSlateSound SelectedPressedSlateSoundOverride;

	/** Optional override for the sound to play when this button is hovered while Selected */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (DisplayName = "Selected Hovered Sound Override"))
	FSlateSound SelectedHoveredSlateSoundOverride;

	/** Optional override for the sound to play when this button is pressed while Locked */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (DisplayName = "Locked Pressed Sound Override"))
	FSlateSound LockedPressedSlateSoundOverride;

	/** Optional override for the sound to play when this button is hovered while Locked */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound", meta = (DisplayName = "Locked Hovered Sound Override"))
	FSlateSound LockedHoveredSlateSoundOverride;

public:
	UFUNCTION(BlueprintCallable)
	void SetPressedSoundOverride(USoundBase* Sound);

	UFUNCTION(BlueprintCallable)
	void SetHoveredSoundOverride(USoundBase* Sound);

	UFUNCTION(BlueprintCallable)
	void SetSelectedPressedSoundOverride(USoundBase* Sound);

	UFUNCTION(BlueprintCallable)
	void SetSelectedHoveredSoundOverride(USoundBase* Sound);

	UFUNCTION(BlueprintCallable)
	void SetLockedPressedSoundOverride(USoundBase* Sound);

	UFUNCTION(BlueprintCallable)
	void SetLockedHoveredSoundOverride(USoundBase* Sound);

	/* ==================== Locked ==================== */
public:
	/**
	 * True if this button is currently locked.
	 * Locked button can be hovered, focused, and pressed, but the Click event will not go through.
	 * Business logic behind it will not be executed. Designed for progressive disclosure
	 */
	UPROPERTY(EditAnywhere, Category = "Locked")
	uint8 bLocked : 1;

public:
	/** True if the button is currently locked, False otherwise */
	UFUNCTION(BlueprintPure)
	bool GetIsLocked() const;

	/** Change whether this widget is locked. If locked, the button can be focusable and responsive to mouse input but will not broadcast OnClicked events. */
	UFUNCTION(BlueprintCallable)
	void SetIsLocked(bool bInIsLocked);

	/* ==================== Selection ==================== */
public:
	/** True if the button supports being in a "selected" state, which will update the style accordingly */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selection")
	uint8 bSelectable : 1;

	/** True if the button can be deselected by clicking it when selected */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selection", meta = ( EditCondition = "bSelectable"))
	uint8 bToggleable : 1;

	/** If true, the button will be selected when it receives focus. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selection", meta = ( EditCondition = "bSelectable"))
	uint8 bShouldSelectUponReceivingFocus : 1;

	/** If true, the button may be clicked while selected. Otherwise, interaction is disabled in the selected state. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selection", meta = ( EditCondition = "bSelectable"))
	uint8 bInteractableWhenSelected : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Selection", meta = ( EditCondition = "bSelectable"))
	uint8 bTriggerClickedAfterSelection : 1;

public:
	/** Change whether this widget is selectable at all. If false and currently selected, will deselect. */
	UFUNCTION(BlueprintCallable)
	void SetIsSelectable(bool bInIsSelectable);

	/** Change whether this widget is toggleable. If toggleable, clicking when selected will deselect. */
	UFUNCTION(BlueprintCallable)
	void SetIsToggleable(bool bInIsToggleable);

	/** Set whether the button should become selected upon receiving focus or not; Only settable for buttons that are selectable */
	UFUNCTION(BlueprintCallable)
	void SetShouldSelectUponReceivingFocus(bool bInShouldSelectUponReceivingFocus);

	/** Change whether this widget is selectable at all. If false and currently selected, will deselect. */
	UFUNCTION(BlueprintCallable)
	void SetIsInteractableWhenSelected(bool bInInteractableWhenSelected);

public:
	/** True if the button is currently in a selected state, False otherwise */
	UFUNCTION(BlueprintPure)
	bool GetIsSelected() const;

	/** Change the selected state manually. */
	UFUNCTION(BlueprintCallable)
	void SetIsSelected(bool InSelected, bool bGiveClickFeedback = true);

	UFUNCTION(BlueprintCallable)
	void ClearSelection();

protected:
	void SetSelectedInternal(bool bInSelected, bool bGiveClickFeedback = true, bool bBroadcast = true);

private:
	/** True if this button is currently selected */
	uint8 bSelected : 1;

	/* ==================== Hold ==================== */
public:
	/** True if this button should have a press and hold behavior, triggering the click when the specified hold time is met */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hold")
	uint8 bRequiresHold : 1;

	/** Press and Hold values used for Keyboard and Mouse, Gamepad and Touch, depending on the current input type */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hold", meta = (EditCondition="bRequiresHold"))
	TSubclassOf<UCommonUIHoldData> HoldData;

protected:
	virtual void HoldReset();

	/** If HoldData is valid, assigns its values to Keyboard and Mouse, Gamepad and Touch, based off the Current Input Type. */
	virtual void UpdateHoldData(ECommonInputType CurrentInputType);

	/** Bound to the hold progress not related to the bound key */
	virtual bool NativeOnHoldProgress(float DeltaTime);

	/** Bound to the hold progress rollback not related to the bound key */
	virtual bool NativeOnHoldProgressRollback(float DeltaTime);

	/** Bound to the hold progress of the bound key from the input action */
	virtual void NativeOnHoldActionProgressed(float HoldPercent);

	virtual void NativeOnHoldActionCompleted();

protected:
	/** Callback fired continously during hold interactions */
	UFUNCTION(BlueprintImplementableEvent)
	void OnHoldActionProgress(float HeldPercent);

	/** Callback fired when hold events complete */
	UFUNCTION(BlueprintImplementableEvent)
	void OnHoldActionCompleted();

protected:
	/** Press and hold time in seconds */
	float HoldTime;

	/**
	* Time (in seconds) for hold progress to go from 1.0 (completed) to 0.0.
	* Used when the press and hold is interrupted.
	* If set to 0, there will be no rollback and the hold progress will reset immediately.
	*/
	float HoldRollbackTime;

	/** Current hold time for this button */
	float CurrentHoldTime;

	/** Handle for ticker spawned for press and hold */
	FTSTicker::FDelegateHandle HoldTickerHandle;

	/** Handle for ticker spawned for button hold rollback */
	FTSTicker::FDelegateHandle HoldRollbackTickerHandle;

	FUIActionBindingHandle TriggeringBindingHandle;

	/* ==================== Input ==================== */
public:
	/** The type of mouse action required by the user to trigger the button's 'Click' */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TEnumAsByte<EButtonClickMethod::Type> ClickMethod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TEnumAsByte<EButtonTouchMethod::Type> TouchMethod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TEnumAsByte<EButtonPressMethod::Type> PressMethod;

	/** True if the input action should be displayed when the button is not interactable */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	uint8 bDisplayInputActionWhenNotInteractable : 1;

	/** True if the input action should be hidden while the user is using a keyboard */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	uint8 bHideInputActionWithKeyboard : 1;

	/** True if this button should use the default fallback input action (bool is useful for buttons that shouldn't because they are never directly hit via controller) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	uint8 bShouldUseFallbackDefaultInputAction : 1;

	/** 
	 *	The input action that is bound to this button. The common input manager will trigger this button to 
	 *	click if the action was pressed 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (RowType = "/Script/CommonUI.CommonInputActionDataBase"))
	FDataTableRowHandle TriggeringInputAction;

	/** 
	 *	The enhanced input action that is bound to this button. The common input manager will trigger this button to 
	 *	click if the action was pressed 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (EditCondition = "CommonInput.CommonInputSettings.IsEnhancedInputSupportEnabled", EditConditionHides))
	TObjectPtr<UInputAction> TriggeringEnhancedInputAction;

	/**
	 * Optionally bound widget for visualization behavior of an input action;
	 * NOTE: If specified, will visualize according to the following algorithm:
	 * If TriggeringEnhancedInputAction is specified, visualize it else:
	 * If TriggeringInputAction is specified, visualize it else:
	 * If TriggeredInputAction is specified, visualize it else:
	 * Visualize the default click action while hovered
	 */
	UPROPERTY(BlueprintReadOnly, Category = "Input", meta = (BindWidgetOptional, AllowPrivateAccess = true))
	TObjectPtr<UCommonActionWidget> InputActionWidget;

	/** True if this button should play the hover effect when pressed by a touch input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", AdvancedDisplay)
	bool bSimulateHoverOnTouchInput = true;

	/**
	 * DANGER! Be very, very careful with this. Unless you absolutely know what you're doing, this is not the property you're looking for.
	 *
	 * True to register the action bound to this button as a "persistent" binding. False (default) will register a standard activation-based binding.
	 * A persistent binding ignores the standard ruleset for UI input routing - the binding will be live immediately upon construction of the button.
	 */
	UPROPERTY(EditAnywhere, Category = "Input", AdvancedDisplay)
	bool bIsPersistentBinding = false;

	//Set this to Game for special cases where an input action needs to be set for an in-game button.
	UPROPERTY(EditAnywhere, Category = "Input", AdvancedDisplay)
	ECommonInputMode InputModeOverride = ECommonInputMode::Menu;

public:
	/** Set the click method for mouse interaction */
	UFUNCTION(BlueprintCallable)
	void SetClickMethod(EButtonClickMethod::Type InClickMethod);

	/** Set the click method for touch interaction */
	UFUNCTION(BlueprintCallable)
	void SetTouchMethod(EButtonTouchMethod::Type InTouchMethod);

	/** Set the click method for keyboard/gamepad button press interaction */
	UFUNCTION(BlueprintCallable)
	void SetPressMethod(EButtonPressMethod::Type InPressMethod);

	/** Change whether this widget should use the fallback default input action. */
	UFUNCTION(BlueprintCallable)
	void SetShouldUseFallbackDefaultInputAction(bool bInShouldUseFallbackDefaultInputAction);

	/** Gets the appropriate input action that is set */
	UFUNCTION(BlueprintCallable)
	bool GetInputAction(FDataTableRowHandle& InputActionRow) const;

	/** Updates the current triggering action */
	UFUNCTION(BlueprintCallable)
	void SetTriggeringInputAction(const FDataTableRowHandle& InputActionRow);

	/** Updates the current triggered action */
	UFUNCTION(BlueprintCallable)
	void SetTriggeredInputAction(const FDataTableRowHandle& InputActionRow);

	/** Gets the appropriate enhanced input action that is set */
	UFUNCTION(BlueprintPure)
	UInputAction* GetTriggeringEnhancedInputAction() const;

	/** Updates the current triggering enhanced input action, requires enhanced input enabled in CommonUI settings */
	UFUNCTION(BlueprintCallable)
	void SetTriggeringEnhancedInputAction(UInputAction* InInputAction);

protected:
	/**
	 * The input action that can be visualized as well as triggered when the user
	 * clicks the button.
	 * 
	 * @TODO: This is part of legacy CommonUI and should be removed
	 */
	FDataTableRowHandle TriggeredInputAction;

	/** Helper function to bind to input method change events */
	virtual void BindInputMethodChangedDelegate();

	/** Helper function to unbind from input method change events */
	virtual void UnbindInputMethodChangedDelegate();

	/** Associates this button at its priority with the given key */
	virtual void BindTriggeringInputActionToClick();

	/** Associates this button at its priority with the given key */
	virtual void UnbindTriggeringInputActionToClick();

	virtual void HandleTriggeringActionCommited();

	bool IsPersistentBinding() const { return bIsPersistentBinding; }

	ECommonInputMode GetInputModeOverride() const { return InputModeOverride; }

	/** Helper function to update the associated input action widget, if any, based upon the state of the button */
	virtual void UpdateInputActionWidget();

	void UpdateInputActionWidgetVisibility() const;

protected:
	/** Callback fired when triggered input action datatable row changes */
	UFUNCTION(BlueprintImplementableEvent)
	void OnTriggeringInputActionChanged(const FDataTableRowHandle& NewTriggeredAction);

	/** Callback fired when input action datatable row changes */
	UFUNCTION(BlueprintImplementableEvent)
	void OnTriggeredInputActionChanged(const FDataTableRowHandle& NewTriggeredAction);

	/** Callback fired when enhanced input action changes */
	UFUNCTION(BlueprintImplementableEvent)
	void OnTriggeringEnhancedInputActionChanged(const UInputAction* InInputAction);

	/* ==================== Interaction ==================== */
public:
	/** Disables this button with a reason (use instead of SetIsEnabled) */
	UFUNCTION(BlueprintCallable)
	void DisableButtonWithReason(const FText& DisabledReason);

	/** Is this button currently interactable? (use instead of GetIsEnabled) */
	UFUNCTION(BlueprintCallable)
	bool IsInteractionEnabled() const;

	/** Change whether this widget is selectable at all. If false and currently selected, will deselect. */
	UFUNCTION(BlueprintCallable)
	void SetIsInteractionEnabled(bool bInIsInteractionEnabled);

private:
	/** True if this button is currently enabled */
	uint8 bButtonEnabled : 1;

	/** True if interaction with this button is currently enabled */
	uint8 bInteractionEnabled : 1;

	FText DisabledTooltipText;

	/** Enables this button (called in SetIsEnabled override) */
	void EnableButton();

	/** Disables this button (called in SetIsEnabled override) */
	void DisableButton();

	/* ==================== UInteractableWidgetBase ==================== */
public:
	/** Gets the bIsFocusable flag */
	UFUNCTION(BlueprintPure)
	bool GetIsFocusable() const;

	/** Updates the bIsFocusable flag */
	UFUNCTION(BlueprintCallable)
	void SetIsFocusable(bool bInIsFocusable);

	/** Is this button currently pressed? */
	UFUNCTION(BlueprintPure)
	bool IsPressed() const;
};
