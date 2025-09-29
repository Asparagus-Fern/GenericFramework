// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericButtonType.h"
#include "Generic/GenericObject.h"
#include "Interface/StateInterface.h"
#include "GenericButtonGroup.generated.h"

class UGenericButtonCollection;
class UButtonGroupViewModel;
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
 * Determines How The Child Buttons Effect Each Other When Accept Input Event
 */
UCLASS(MinimalAPI)
class UGenericButtonGroup : public UGenericObject, public IStateInterface
{
	GENERATED_BODY()

	/* IStateInterface */
public:
	virtual void NativeOnCreate() override;
	virtual void NativeOnDestroy() override;

	/* UInteractableWidgetEntityGroup */
public:
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API UGenericButtonContainer* GetButtonGroupWidget();

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetButtonGroupWidget(UGenericButtonContainer* InButtonGroupWidget);

public:
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void AddButtons(const TArray<UGenericButtonWidget*>& InButtons);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void AddButton(UGenericButtonWidget* InButton);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void RemoveButtons(const TArray<UGenericButtonWidget*>& InButtons);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void RemoveButtonByIndex(int32 InIndex);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void RemoveButton(UGenericButtonWidget* InButton);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void ClearAllButton();

public:
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API TArray<UGenericButtonWidget*> GetAllButton() const;

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API int32 GetButtonCount() const;

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API bool HasButton(UGenericButtonWidget* InButton) const;

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API UGenericButtonWidget* GetButtonByIndex(int32 InIndex);

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API int32 FindButtonIndex(UGenericButtonWidget* InButton) const;

public:
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API bool HasLastSelectedButton() const;

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API bool HasSelectedButton() const;

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API UGenericButtonWidget* GetLastSelectedButton() const;

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API int32 GetLastSelectedButtonIndex() const;

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API UGenericButtonWidget* GetSelectedButton() const;

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetSelectedButton(UGenericButtonWidget* InButton);

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API int32 GetSelectedButtonIndex() const;

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetSelectedButtonByIndex(int32 InIndex);

public:
	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SelectLastButton();

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SelectPreviousButton(bool bAllowWrapping);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SelectNextButton(bool bAllowWrapping);

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void DeselectAll();

	/* Binding From Widget (If Exist) */
protected:
	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonPressed(UGenericButtonWidget* Button);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonReleased(UGenericButtonWidget* Button);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonHovered(UGenericButtonWidget* Button);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonUnhovered(UGenericButtonWidget* Button);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonClicked(UGenericButtonWidget* Button);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonDoubleClicked(UGenericButtonWidget* Button);

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void HandleOnButtonSelectionChanged(UGenericButtonWidget* Button, bool Selection);

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

public:
	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API virtual UGenericButtonCollection* GetButtonCollection() const;

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API UButtonGroupViewModel* GetButtonGroupViewModel();

	UFUNCTION(BlueprintCallable)
	WIDGETGROUPGENERATION_API void SetButtonGroupViewModel(UButtonGroupViewModel* InButtonGroupViewModel);

private:
	UPROPERTY()
	TWeakObjectPtr<UGenericButtonCollection> ButtonCollection = nullptr;

	UPROPERTY()
	TObjectPtr<UButtonGroupViewModel> ButtonGroupViewModel = nullptr;
};
