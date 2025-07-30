// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ButtonType.h"
#include "NativeGameplayTags.h"
#include "Base/GenericWidget.h"
#include "GenericButtonWidget.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Button);

class UGenericButtonStyle;
class UGenericButton;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractableWidgetEvent, UGenericButtonWidget*, Button);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectedStateChangedEvent, UGenericButtonWidget*, Button, bool, IsSelected);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonLockEvent, UGenericButtonWidget*, Button, bool, IsLocked);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonHoldingEvent, UGenericButtonWidget*, Button, float, Percent);

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
	UGenericButtonWidget(const FObjectInitializer& ObjectInitializer);

	//~ Begin UWidget interface
	virtual void SynchronizeProperties() override;
	virtual void SetIsEnabled(bool bInIsEnabled) override;
	virtual bool IsHovered() const override;
	//~ End UWidget Interface

	//~ Begin UUserWidget interface
	virtual bool Initialize() override;
	virtual bool NativeIsInteractable() const override;
	virtual FReply NativeOnFocusReceived(const FGeometry& InGeometry, const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnFocusLost(const FFocusEvent& InFocusEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	//~ End UUserWidget Interface

	/* Gets the bIsFocusable flag */
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API bool GetButtonFocusable() const;

	/* Updates the bIsFocusable flag */
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetButtonFocusable(bool bInIsFocusable);

	void NativeConstructButtonParameters(const FButtonParameter& ButtonParameter);
	UFUNCTION(BlueprintImplementableEvent)
	void ConstructButtonParameters(const FButtonParameter& ButtonParameter);

private:
	virtual UGenericButton* ConstructInternalButton();
	TWeakObjectPtr<class UGenericButton> RootButton;

	/* ==================== Event ==================== */
protected:
	/* Helper function registered to the underlying button when pressed */
	UFUNCTION()
	void HandleButtonPressed();

	/* Helper function registered to the underlying button when released */
	UFUNCTION()
	void HandleButtonReleased();

	/* Handler function registered to the underlying button's click. */
	UFUNCTION()
	void HandleButtonClicked();

	/* Handler function registered to the underlying button's double click. */
	UFUNCTION()
	void HandleButtonDoubleClicked();

	/* Helper function registered to the underlying button receiving focus */
	UFUNCTION()
	virtual void HandleFocusReceived();

	/* Helper function registered to the underlying button losing focus */
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
	void HandleOnButtonStyleChanged();

public:
	UPROPERTY(meta=(BindWidgetAnimOptional), Transient)
	TObjectPtr<UWidgetAnimation> HoveredAnimation = nullptr;

	UPROPERTY(meta=(BindWidgetAnimOptional), Transient)
	TObjectPtr<UWidgetAnimation> SelectedAnimation = nullptr;

	/* ==================== Style ==================== */
public:
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
	void RefreshDimensions() const;

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
	WIDGETGROUPGENERATION_API void SetIsSelected(bool InSelected, bool bGiveClickFeedback = true);

protected:
	void SetSelectedInternal(bool bInSelected, bool bGiveClickFeedback = true, bool bBroadcast = true);

private:
	/* True if this button is currently selected */
	uint8 bSelected : 1;

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
};
