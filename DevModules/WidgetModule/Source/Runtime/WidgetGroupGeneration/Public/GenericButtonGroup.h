// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericObject.h"
#include "GenericButtonGroup.generated.h"

class UGenericButtonContainer;
class UGenericButtonWidget;
class UGenericButtonGroup;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonPressed, UGenericButtonGroup*, ButtonGroup, UGenericButtonWidget*, Button);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonReleased, UGenericButtonGroup*, ButtonGroup, UGenericButtonWidget*, Button);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonHovered, UGenericButtonGroup*, ButtonGroup, UGenericButtonWidget*, Button);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonUnhovered, UGenericButtonGroup*, ButtonGroup, UGenericButtonWidget*, Button);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonClicked, UGenericButtonGroup*, ButtonGroup, UGenericButtonWidget*, Button);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDoubleClicked, UGenericButtonGroup*, ButtonGroup, UGenericButtonWidget*, Button);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnButtonSelectionChanged, UGenericButtonGroup*, ButtonGroup, UGenericButtonWidget*, Button, bool, Selection);

/**
 * 
 */
UCLASS()
class WIDGETGROUPGENERATION_API UGenericButtonGroup : public UGenericObject
{
	GENERATED_BODY()

	/* UInteractableWidgetEntityGroup */

public:
	UFUNCTION(BlueprintPure)
	UGenericButtonContainer* GetButtonGroupWidget();

	UFUNCTION(BlueprintCallable)
	void SetButtonGroupWidget(UGenericButtonContainer* InButtonGroupWidget);

public:
	UFUNCTION(BlueprintCallable)
	void AddButtons(const TArray<UGenericButtonWidget*>& InButtons);

	UFUNCTION(BlueprintCallable)
	void AddButton(UGenericButtonWidget* InButton);

	UFUNCTION(BlueprintCallable)
	void RemoveButtons(const TArray<UGenericButtonWidget*>& InButtons);

	UFUNCTION(BlueprintCallable)
	void RemoveButtonByIndex(int32 InIndex);

	UFUNCTION(BlueprintCallable)
	void RemoveButton(UGenericButtonWidget* InButton);

	UFUNCTION(BlueprintCallable)
	void ClearAllButton();

public:
	UFUNCTION(BlueprintPure)
	TArray<UGenericButtonWidget*> GetAllButton() const;

	UFUNCTION(BlueprintPure)
	int32 GetButtonCount() const;

	UFUNCTION(BlueprintPure)
	bool HasButton(UGenericButtonWidget* InButton) const;

	UFUNCTION(BlueprintPure)
	UGenericButtonWidget* GetButtonByIndex(int32 InIndex);

	UFUNCTION(BlueprintPure)
	int32 FindButtonIndex(UGenericButtonWidget* InButton) const;

public:
	UFUNCTION(BlueprintPure)
	bool HasLastSelectedButton() const;

	UFUNCTION(BlueprintPure)
	bool HasSelectedButton() const;

	UFUNCTION(BlueprintPure)
	UGenericButtonWidget* GetLastSelectedButton() const;

	UFUNCTION(BlueprintPure)
	int32 GetLastSelectedButtonIndex() const;

	UFUNCTION(BlueprintPure)
	UGenericButtonWidget* GetSelectedButton() const;

	UFUNCTION(BlueprintCallable)
	void SetSelectedButton(UGenericButtonWidget* InButton);

	UFUNCTION(BlueprintPure)
	int32 GetSelectedButtonIndex() const;

	UFUNCTION(BlueprintCallable)
	void SetSelectedButtonByIndex(int32 InIndex);

public:
	UFUNCTION(BlueprintCallable)
	void SelectLastButton();

	UFUNCTION(BlueprintCallable)
	void SelectPreviousButton(bool bAllowWrapping);

	UFUNCTION(BlueprintCallable)
	void SelectNextButton(bool bAllowWrapping);

	UFUNCTION(BlueprintCallable)
	void DeselectAll();

	/* Binding From Widget (If Exist) */
private:
	UFUNCTION()
	virtual void HandleOnButtonPressed(UGenericButtonWidget* Button);

	UFUNCTION()
	virtual void HandleOnButtonReleased(UGenericButtonWidget* Button);

	UFUNCTION()
	virtual void HandleOnButtonHovered(UGenericButtonWidget* Button);

	UFUNCTION()
	virtual void HandleOnButtonUnhovered(UGenericButtonWidget* Button);

	UFUNCTION()
	virtual void HandleOnButtonClicked(UGenericButtonWidget* Button);

	UFUNCTION()
	virtual void HandleOnButtonDoubleClicked(UGenericButtonWidget* Button);

	UFUNCTION()
	virtual void HandleOnButtonSelectionChanged(UGenericButtonWidget* Button, bool Selection);

public:
	UPROPERTY(BlueprintAssignable)
	FOnButtonPressed OnButtonPressed;

	UPROPERTY(BlueprintAssignable)
	FOnButtonReleased OnButtonReleased;

	UPROPERTY(BlueprintAssignable)
	FOnButtonHovered OnButtonHovered;

	UPROPERTY(BlueprintAssignable)
	FOnButtonUnhovered OnButtonUnhovered;

	UPROPERTY(BlueprintAssignable)
	FOnButtonClicked OnButtonClicked;

	UPROPERTY(BlueprintAssignable)
	FOnButtonDoubleClicked OnButtonDoubleClicked;

	UPROPERTY(BlueprintAssignable)
	FOnButtonSelectionChanged OnButtonSelectionChanged;

protected:
	UPROPERTY()
	TObjectPtr<UGenericButtonWidget> LastSelectedButton = nullptr;

	UPROPERTY()
	TObjectPtr<UGenericButtonWidget> SelectedButton = nullptr;

	UPROPERTY()
	TObjectPtr<UGenericButtonContainer> ButtonGroupWidget;

	UPROPERTY()
	TArray<TObjectPtr<UGenericButtonWidget>> ButtonWidgets;
};
