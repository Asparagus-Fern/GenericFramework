// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GenericButtonType.h"
#include "Base/GenericWidget.h"
#include "GenericButtonWidget.generated.h"

class UButtonSoundViewModel;
class UButtonInputViewModel;
class UButtonSelectionViewModel;
class UGenericButtonStyle;
class UGenericButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractableWidgetEvent, UGenericButtonWidget*, Button);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectedStateChangedEvent, UGenericButtonWidget*, Button, bool, IsSelected);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonLockEvent, UGenericButtonWidget*, Button, bool, IsLocked);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonHoldingEvent, UGenericButtonWidget*, Button, float, Percent);

UENUM(BlueprintType)
enum class EDesiredButtonStyle : uint8
{
	Normal,
	Selected,
	Locked,
	Disabled
};

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericButtonWidget : public UGenericWidget
{
	GENERATED_BODY()

	friend class UGenericButtonGroup;

	/* ==================== UGenericButtonWidget ==================== */
public:
	WIDGETGROUPGENERATION_API UGenericButtonWidget(const FObjectInitializer& ObjectInitializer);

	//~ Begin UWidget interface
	WIDGETGROUPGENERATION_API virtual void SynchronizeProperties() override;
	WIDGETGROUPGENERATION_API virtual void SetIsEnabled(bool bInIsEnabled) override;
	WIDGETGROUPGENERATION_API virtual bool IsHovered() const override;
	//~ End UWidget Interface

	//~ Begin UUserWidget interface
	WIDGETGROUPGENERATION_API virtual bool Initialize() override;
	WIDGETGROUPGENERATION_API virtual void NativePreConstruct() override;
	WIDGETGROUPGENERATION_API virtual void NativeConstruct() override;
	WIDGETGROUPGENERATION_API virtual void NativeDestruct() override;
	WIDGETGROUPGENERATION_API virtual bool NativeIsInteractable() const override;
	WIDGETGROUPGENERATION_API virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	WIDGETGROUPGENERATION_API virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;
	WIDGETGROUPGENERATION_API virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	WIDGETGROUPGENERATION_API virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	//~ End UUserWidget Interface

	/* Gets the bIsFocusable flag */
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API bool GetButtonFocusable() const;

	/* Updates the bIsFocusable flag */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetButtonFocusable(bool bInIsFocusable);

protected:
	WIDGETGROUPGENERATION_API virtual UGenericButton* ConstructInternalButton();
	TWeakObjectPtr<class UGenericButton> RootButton;

	/* ==================== Input ==================== */
public:
	/* The type of mouse action required by the user to trigger the button's 'Click' */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic Button Widget | Input")
	TEnumAsByte<EButtonClickMethod::Type> ClickMethod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic Button Widget | Input")
	TEnumAsByte<EButtonTouchMethod::Type> TouchMethod;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic Button Widget | Input")
	TEnumAsByte<EButtonPressMethod::Type> PressMethod;

public:
	/* Set the click method for mouse interaction */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetClickMethod(EButtonClickMethod::Type InClickMethod);

	/* Set the click method for touch interaction */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetTouchMethod(EButtonTouchMethod::Type InTouchMethod);

	/* Set the click method for keyboard/gamepad button press interaction */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetPressMethod(EButtonPressMethod::Type InPressMethod);

public:
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API UButtonInputViewModel* GetButtonInputViewModel() const;

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetButtonInputViewModel(UButtonInputViewModel* InViewModel);

protected:
	UFUNCTION(BlueprintNativeEvent, Category="Button Input View Model")
	WIDGETGROUPGENERATION_API void OnClickMethodChanged(EButtonClickMethod::Type InClickMethod);

	UFUNCTION(BlueprintNativeEvent, Category="Button Input View Model")
	WIDGETGROUPGENERATION_API void OnTouchMethodChanged(EButtonTouchMethod::Type InTouchMethod);

	UFUNCTION(BlueprintNativeEvent, Category="Button Input View Model")
	WIDGETGROUPGENERATION_API void OnPressMethodChanged(EButtonPressMethod::Type InPressMethod);

	UPROPERTY(VisibleAnywhere, Getter, Setter, BlueprintGetter="GetButtonInputViewModel", BlueprintSetter="SetButtonInputViewModel", Category = "Generic Button Widget | ViewModel")
	TObjectPtr<UButtonInputViewModel> ButtonInputViewModel = nullptr;

	/* ==================== Interaction ==================== */
public:
	/* Is this button currently interactable? (use instead of GetIsEnabled) */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API bool GetIsInteractionEnabled() const;

	/* Change whether this widget is selectable at all. If false and currently selected, will deselect. */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetIsInteractionEnabled(bool bInIsInteractionEnabled);

private:
	/* True if this button is currently enabled */
	uint8 bButtonEnabled : 1;

	/* True if interaction with this button is currently enabled */
	uint8 bInteractionEnabled : 1;

	/* Enables this button (called in SetIsEnabled override) */
	void EnableButton();

	/* Disables this button (called in SetIsEnabled override) */
	void DisableButton();

	/* ==================== Event ==================== */
protected:
	/* Helper function registered to the underlying button when pressed */
	UFUNCTION()
	WIDGETGROUPGENERATION_API void HandleButtonPressed();

	/* Helper function registered to the underlying button when released */
	UFUNCTION()
	WIDGETGROUPGENERATION_API void HandleButtonReleased();

	/* Handler function registered to the underlying button's click. */
	UFUNCTION()
	WIDGETGROUPGENERATION_API void HandleButtonClicked();

	/* Handler function registered to the underlying button's double click. */
	UFUNCTION()
	WIDGETGROUPGENERATION_API void HandleButtonDoubleClicked();

	/* Helper function registered to the underlying button receiving focus */
	UFUNCTION()
	WIDGETGROUPGENERATION_API virtual void HandleFocusReceived();

	/* Helper function registered to the underlying button losing focus */
	UFUNCTION()
	WIDGETGROUPGENERATION_API virtual void HandleFocusLost();

	/* ==================== Selection ==================== */
public:
	/**
	 * True if this button is currently locked.
	 * Locked button can be hovered, focused, and pressed, but the Click event will not go through.
	 * Business logic behind it will not be executed. Designed for progressive disclosure
	 */
	UPROPERTY(EditAnywhere, Category = "Generic Button Widget | Selection")
	uint8 bLocked : 1;

	/* True if the button supports being in a "selected" state, which will update the style accordingly */
	UPROPERTY(EditAnywhere, Category = "Generic Button Widget | Selection")
	uint8 bSelectable : 1;

	/* True if the button can be deselected by clicking it when selected */
	UPROPERTY(EditAnywhere, Category = "Generic Button Widget | Selection", meta = (EditConditionHides, EditCondition = "bSelectable"))
	uint8 bToggleable : 1;

	/* If True, the button will be selected when it actived */
	UPROPERTY(EditAnywhere, Category = "Generic Button Widget | Selection", meta=(EditConditionHides, EditCondition = "bSelectable"))
	bool bDefaultSelected = false;

	/* If true, the button will be selected when it receives focus. */
	UPROPERTY(EditAnywhere, Category = "Generic Button Widget | Selection", meta = (EditConditionHides, EditCondition = "bSelectable"))
	uint8 bSelectedWhenReceiveFocus : 1;

	/* If true, the button may be clicked while selected. Otherwise, interaction is disabled in the selected state. */
	UPROPERTY(EditAnywhere, Category = "Generic Button Widget | Selection", meta = (EditConditionHides, EditCondition = "bSelectable && !bToggleable"))
	uint8 bInteractableWhenSelected : 1;

	UPROPERTY(EditAnywhere, Category = "Generic Button Widget | Selection", meta = (EditConditionHides, EditCondition = "bSelectable"))
	uint8 bTriggerClickedAfterSelection : 1;

public:
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API bool GetIsLocked() const;

	/* Change whether this widget is locked. If locked, the button can be focusable and responsive to mouse input but will not broadcast OnClicked events. */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetIsLocked(bool bInIsLocked);

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API bool GetIsSelectable() const;

	/* Change whether this widget is selectable at all. If false and currently selected, will deselect. */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetIsSelectable(bool bInIsSelectable);

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API bool GetIsToggleable() const;

	/* Change whether this widget is toggleable. If toggleable, clicking when selected will deselect. */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetIsToggleable(bool bInIsToggleable);

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API bool GetIsDefaultSelected() const;

	/* Change whether this widget is Default Selected. */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetIsDefaultSelected(bool bInDefaultSelected);

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API bool GetIsSelectedWhenReceiveFocus() const;

	/* Set whether the button should become selected upon receiving focus or not; Only settable for buttons that are selectable */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetIsSelectedWhenReceiveFocus(bool bInSelectedWhenReceiveFocus);

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API bool GetIsInteractableWhenSelected() const;

	/* Change whether this widget is selectable when currently selected. */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetIsInteractableWhenSelected(bool bInInteractableWhenSelected);

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API bool GetIsTriggerClickedAfterSelection() const;

	/* Change whether the button click event call after selected event */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetIsTriggerClickedAfterSelection(bool bInTriggerClickedAfterSelection);

	/* True if the button is currently in a selected state, False otherwise */
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API bool GetIsSelected() const;

	/* Change the selected state manually. */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetIsSelected(bool InSelected);

public:
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API UButtonSelectionViewModel* GetButtonSelectionViewModel() const;

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetButtonSelectionViewModel(UButtonSelectionViewModel* InViewModel);

protected:
	UFUNCTION(BlueprintNativeEvent, Category="Button Selection View Model")
	WIDGETGROUPGENERATION_API void OnSelectableChanged(bool IsSelectable);

	UFUNCTION(BlueprintNativeEvent, Category="Button Selection View Model")
	WIDGETGROUPGENERATION_API void OnToggleableChanged(bool IsToggleable);

	UFUNCTION(BlueprintNativeEvent, Category="Button Selection View Model")
	WIDGETGROUPGENERATION_API void OnDefaultSelectedChanged(bool IsDefaultSelected);

	UFUNCTION(BlueprintNativeEvent, Category="Button Selection View Model")
	WIDGETGROUPGENERATION_API void OnShouldSelectUponReceivingFocusChanged(bool IsShouldSelectUponReceivingFocus);

	UFUNCTION(BlueprintNativeEvent, Category="Button Selection View Model")
	WIDGETGROUPGENERATION_API void OnInteractableWhenSelectedChanged(bool IsInteractableWhenSelected);

	UFUNCTION(BlueprintNativeEvent, Category="Button Selection View Model")
	WIDGETGROUPGENERATION_API void OnTriggerClickedAfterSelectionChanged(bool IsTriggerClickedAfterSelection);

	UPROPERTY(VisibleAnywhere, Instanced, Getter, Setter, BlueprintGetter="GetButtonSelectionViewModel", BlueprintSetter="SetButtonSelectionViewModel", Category = "Generic Button Widget | ViewModel")
	TObjectPtr<UButtonSelectionViewModel> ButtonSelectionViewModel = nullptr;

private:
	/* True if this button is currently selected */
	uint8 bSelected : 1;

	/* ==================== Event Confirm ==================== */
public:
	DECLARE_DELEGATE_RetVal_OneParam(bool, FButtonConfirmEvent, UGenericButtonWidget*);
	DECLARE_DELEGATE_RetVal_TwoParams(bool, FButtonSelectionConfirmEvent, UGenericButtonWidget*, bool NewSelection);

	WIDGETGROUPGENERATION_API FButtonConfirmEvent& GetOnButtonPressedConfirmedEvent() { return OnButtonPressedConfirmedEvent; }
	WIDGETGROUPGENERATION_API FButtonConfirmEvent& GetOnButtonReleasedConfirmedEvent() { return OnButtonReleasedConfirmedEvent; }
	WIDGETGROUPGENERATION_API FButtonConfirmEvent& GetOnButtonHoveredConfirmedEvent() { return OnButtonHoveredConfirmedEvent; }
	WIDGETGROUPGENERATION_API FButtonConfirmEvent& GetOnButtonUnhoveredConfirmedEvent() { return OnButtonUnhoveredConfirmedEvent; }
	WIDGETGROUPGENERATION_API FButtonConfirmEvent& GetOnButtonClickedConfirmedEvent() { return OnButtonClickedConfirmedEvent; }
	WIDGETGROUPGENERATION_API FButtonConfirmEvent& GetOnButtonDoubleClickedConfirmedEvent() { return OnButtonDoubleClickedConfirmedEvent; }
	WIDGETGROUPGENERATION_API FButtonSelectionConfirmEvent& GetOnButtonSelectionConfirmedEvent() { return OnButtonSelectionConfirmedEvent; }

protected:
	WIDGETGROUPGENERATION_API void SetButtonPressedInternal();
	WIDGETGROUPGENERATION_API virtual bool CanButtonPressedInternal();
	WIDGETGROUPGENERATION_API virtual void OnButtonPressedInternal();

	WIDGETGROUPGENERATION_API void SetButtonReleasedInternal();
	WIDGETGROUPGENERATION_API virtual bool CanButtonReleasedInternal();
	WIDGETGROUPGENERATION_API virtual void OnButtonReleasedInternal();

	WIDGETGROUPGENERATION_API void SetButtonHoveredInternal();
	WIDGETGROUPGENERATION_API virtual bool CanButtonHoveredInternal();
	WIDGETGROUPGENERATION_API virtual void OnButtonHoveredInternal();

	WIDGETGROUPGENERATION_API void SetButtonUnhoveredInternal();
	WIDGETGROUPGENERATION_API virtual bool CanButtonUnhoveredInternal();
	WIDGETGROUPGENERATION_API virtual void OnButtonUnhoveredInternal();

	WIDGETGROUPGENERATION_API void SetButtonClickedInternal();
	WIDGETGROUPGENERATION_API virtual bool CanButtonClickedInternal();
	WIDGETGROUPGENERATION_API virtual void OnButtonClickedInternal();

	WIDGETGROUPGENERATION_API void SetButtonDoubleClickedInternal();
	WIDGETGROUPGENERATION_API virtual bool CanButtonDoubleClickedInternal();
	WIDGETGROUPGENERATION_API virtual void OnButtonDoubleClickedInternal();

	WIDGETGROUPGENERATION_API void SetSelectedInternal(bool bInSelected);
	WIDGETGROUPGENERATION_API virtual bool CanButtonSelectionInternal(bool bInSelected);
	WIDGETGROUPGENERATION_API virtual void OnButtonSelectionInternal(bool bInSelected);

private:
	FButtonConfirmEvent OnButtonPressedConfirmedEvent;
	FButtonConfirmEvent OnButtonReleasedConfirmedEvent;
	FButtonConfirmEvent OnButtonHoveredConfirmedEvent;
	FButtonConfirmEvent OnButtonUnhoveredConfirmedEvent;
	FButtonConfirmEvent OnButtonClickedConfirmedEvent;
	FButtonConfirmEvent OnButtonDoubleClickedConfirmedEvent;
	FButtonSelectionConfirmEvent OnButtonSelectionConfirmedEvent;

	/* ==================== Event Handle ==================== */
protected:
	WIDGETGROUPGENERATION_API virtual void NativeOnEnabled();
	WIDGETGROUPGENERATION_API virtual void NativeOnDisabled();
	WIDGETGROUPGENERATION_API virtual void NativeOnPressed();
	WIDGETGROUPGENERATION_API virtual void NativeOnReleased();
	WIDGETGROUPGENERATION_API virtual void NativeOnHovered();
	WIDGETGROUPGENERATION_API virtual void NativeOnUnhovered();
	WIDGETGROUPGENERATION_API virtual void NativeOnClicked();
	WIDGETGROUPGENERATION_API virtual void NativeOnDoubleClicked();
	WIDGETGROUPGENERATION_API virtual void NativeOnSelected();
	WIDGETGROUPGENERATION_API virtual void NativeOnDeselected();
	WIDGETGROUPGENERATION_API virtual void NativeOnFocusReceived();
	WIDGETGROUPGENERATION_API virtual void NativeOnFocusLost();
	WIDGETGROUPGENERATION_API virtual void NativeOnLockedChanged(bool bIsLocked);
	WIDGETGROUPGENERATION_API virtual void NativeOnLockClicked();
	WIDGETGROUPGENERATION_API virtual void NativeOnLockDoubleClicked();
	WIDGETGROUPGENERATION_API virtual void NativeOnButtonStyleChanged();

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
	FInteractableWidgetEvent OnButtonStyleChanged;

public:
	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonEnabled();

	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonDisabled();

	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonPressed();

	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonReleased();

	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonHovered();

	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonUnhovered();

	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonClicked();

	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonDoubleClicked();

	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonSelectionChanged(bool IsSelected);

	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonFocusReceived();

	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonFocusLost();

	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonLockedChanged(bool IsLock);

	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonLockClicked();

	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonLockDoubleClicked();

	UFUNCTION(BlueprintImplementableEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonStyleChanged();

public:
	UPROPERTY(meta=(BindWidgetAnimOptional), Transient)
	TObjectPtr<UWidgetAnimation> HoveredAnimation = nullptr;

	UPROPERTY(meta=(BindWidgetAnimOptional), Transient)
	TObjectPtr<UWidgetAnimation> SelectedAnimation = nullptr;

	/* ==================== Style ==================== */
public:
#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "Generic Button Widget | Style")
	EDesiredButtonStyle DesiredButtonStyle = EDesiredButtonStyle::Normal;
#endif

	/* The minimum width of the button (only used if greater than the style's minimum) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic Button Widget | Style", meta = (ClampMin = "0"))
	int32 MinWidth;

	/* The minimum height of the button (only used if greater than the style's minimum) */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic Button Widget | Style", meta = (ClampMin = "0"))
	int32 MinHeight;

	UPROPERTY(EditAnywhere, Category = "Generic Button Widget | Style")
	TSubclassOf<UGenericButtonStyle> NormalStyle;

	UPROPERTY(EditAnywhere, Category = "Generic Button Widget | Style")
	TSubclassOf<UGenericButtonStyle> SelectedStyle;

	UPROPERTY(EditAnywhere, Category = "Generic Button Widget | Style")
	TSubclassOf<UGenericButtonStyle> LockedStyle;

	UPROPERTY(EditAnywhere, Category = "Generic Button Widget | Style")
	TSubclassOf<UGenericButtonStyle> DisabledStyle;

public:
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetMinWidth(int32 InMinWidth);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetMinHeight(int32 InMinHeight);

protected:
	WIDGETGROUPGENERATION_API void RefreshDimensions() const;

private:
	const UGenericButtonStyle* GetStyleCDO(const TSubclassOf<UGenericButtonStyle>& InClass) const;
	void UpdateInternalStyle(const TSubclassOf<UGenericButtonStyle>& InClass, FButtonStyle& OutStyle) const;
	void BuildStyles();
	void SetButtonStyle();

	/* Internally managed and applied style to use when not selected */
	UPROPERTY()
	FButtonStyle InternalNormalStyle;

	/* Internally managed and applied style to use when selected */
	UPROPERTY()
	FButtonStyle InternalSelectedStyle;

	/* Internally managed and applied style to use when locked */
	UPROPERTY()
	FButtonStyle InternalLockedStyle;

	/* Internally managed and applied style to use when disabled */
	UPROPERTY()
	FButtonStyle InternalDisabledStyle;

	/* ==================== Sound ==================== */
public:
	/* Optional override for the sound to play when this button is hovered. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic Button Widget | Sound", meta = (DisplayName = "Hovered Sound Override"))
	FSlateSound HoveredSlateSoundOverride;

	/* Optional override for the sound to play when this button is pressed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic Button Widget | Sound", meta = (DisplayName = "Pressed Sound Override"))
	FSlateSound PressedSlateSoundOverride;

	/* Optional override for the sound to play when this button is hovered while Selected */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic Button Widget | Sound", meta = (DisplayName = "Selected Hovered Sound Override"))
	FSlateSound SelectedHoveredSlateSoundOverride;

	/* Optional override for the sound to play when this button is pressed while Selected */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic Button Widget | Sound", meta = (DisplayName = "Selected Pressed Sound Override"))
	FSlateSound SelectedPressedSlateSoundOverride;

	/* Optional override for the sound to play when this button is hovered while Locked */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic Button Widget | Sound", meta = (DisplayName = "Locked Hovered Sound Override"))
	FSlateSound LockedHoveredSlateSoundOverride;

	/* Optional override for the sound to play when this button is pressed while Locked */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Generic Button Widget | Sound", meta = (DisplayName = "Locked Pressed Sound Override"))
	FSlateSound LockedPressedSlateSoundOverride;

public:
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetHoveredSoundOverride(USoundBase* Sound);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetHoveredSlateSoundOverride(const FSlateSound& Sound);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetPressedSoundOverride(USoundBase* Sound);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetPressedSlateSoundOverride(const FSlateSound& Sound);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetSelectedHoveredSoundOverride(USoundBase* Sound);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetSelectedHoveredSlateSoundOverride(const FSlateSound& Sound);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetSelectedPressedSoundOverride(USoundBase* Sound);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetSelectedPressedSlateSoundOverride(const FSlateSound& Sound);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetLockedHoveredSoundOverride(USoundBase* Sound);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetLockedHoveredSlateSoundOverride(const FSlateSound& Sound);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetLockedPressedSoundOverride(USoundBase* Sound);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetLockedPressedSlateSoundOverride(const FSlateSound& Sound);

public:
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API UButtonSoundViewModel* GetButtonSoundViewModel() const;

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetButtonSoundViewModel(UButtonSoundViewModel* InViewModel);

protected:
	UFUNCTION(BlueprintNativeEvent, Category="Button Sound View Model")
	WIDGETGROUPGENERATION_API void OnHoveredSlateSoundOverrideChanged(FSlateSound InSlateSound);

	UFUNCTION(BlueprintNativeEvent, Category="Button Sound View Model")
	WIDGETGROUPGENERATION_API void OnPressedSlateSoundOverrideChanged(FSlateSound InSlateSound);

	UFUNCTION(BlueprintNativeEvent, Category="Button Sound View Model")
	WIDGETGROUPGENERATION_API void OnSelectedHoveredSlateSoundOverrideChanged(FSlateSound InSlateSound);

	UFUNCTION(BlueprintNativeEvent, Category="Button Sound View Model")
	WIDGETGROUPGENERATION_API void OnSelectedPressedSlateSoundOverrideChanged(FSlateSound InSlateSound);

	UFUNCTION(BlueprintNativeEvent, Category="Button Sound View Model")
	WIDGETGROUPGENERATION_API void OnLockedHoveredSlateSoundOverrideChanged(FSlateSound InSlateSound);

	UFUNCTION(BlueprintNativeEvent, Category="Button Sound View Model")
	WIDGETGROUPGENERATION_API void OnLockedPressedSlateSoundOverrideChanged(FSlateSound InSlateSound);

	UPROPERTY(VisibleAnywhere, Instanced, Getter, Setter, BlueprintGetter="GetButtonSoundViewModel", BlueprintSetter="SetButtonSoundViewModel", Category = "Generic Button Widget | ViewModel")
	TObjectPtr<UButtonSoundViewModel> ButtonSoundViewModel = nullptr;
};
