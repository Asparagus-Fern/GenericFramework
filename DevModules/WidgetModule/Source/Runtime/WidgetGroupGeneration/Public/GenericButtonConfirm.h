// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Generic/GenericObject.h"
#include "GenericButtonConfirm.generated.h"

class UGenericButtonWidget;
class UGenericButtonGroup;
class UGenericButtonCollection;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UGenericButtonConfirm : public UGenericObject
{
	GENERATED_BODY()

	/* UGenericButtonConfirm */
public:
	DECLARE_DELEGATE(FButtonConfirmEvent)
	DECLARE_DELEGATE_OneParam(FButtonSelectionConfirmEvent, bool)

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API UGenericButtonCollection* GetButtonCollection() const;
	WIDGETGROUPGENERATION_API void SetButtonCollection(UGenericButtonCollection* InButtonCollection);

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API UGenericButtonGroup* GetButtonGroup() const;
	WIDGETGROUPGENERATION_API void SetButtonGroup(UGenericButtonGroup* InButtonGroup);

	UFUNCTION(BlueprintPure)
	WIDGETGROUPGENERATION_API UGenericButtonWidget* GetButtonWidget() const;

	WIDGETGROUPGENERATION_API FButtonConfirmEvent& GetConfirmButtonPressedEvent() { return ConfirmButtonPressedEvent; }
	WIDGETGROUPGENERATION_API FButtonConfirmEvent& GetConfirmButtonReleasedEvent() { return ConfirmButtonReleasedEvent; }
	WIDGETGROUPGENERATION_API FButtonConfirmEvent& GetConfirmButtonHoveredEvent() { return ConfirmButtonHoveredEvent; }
	WIDGETGROUPGENERATION_API FButtonConfirmEvent& GetConfirmButtonUnhoveredEvent() { return ConfirmButtonUnhoveredEvent; }
	WIDGETGROUPGENERATION_API FButtonConfirmEvent& GetConfirmButtonClickedEvent() { return ConfirmButtonClickedEvent; }
	WIDGETGROUPGENERATION_API FButtonConfirmEvent& GetConfirmButtonDoubleClickedEvent() { return ConfirmButtonDoubleClickedEvent; }
	WIDGETGROUPGENERATION_API FButtonSelectionConfirmEvent& GetConfirmSelectionChangedEvent() { return ConfirmSelectionChangedEvent; }

	WIDGETGROUPGENERATION_API virtual void ConfirmButtonPressed();
	WIDGETGROUPGENERATION_API virtual void ConfirmButtonReleased();
	WIDGETGROUPGENERATION_API virtual void ConfirmButtonHovered();
	WIDGETGROUPGENERATION_API virtual void ConfirmButtonUnhovered();
	WIDGETGROUPGENERATION_API virtual void ConfirmButtonClicked();
	WIDGETGROUPGENERATION_API virtual void ConfirmButtonDoubleClicked();
	WIDGETGROUPGENERATION_API virtual void ConfirmButtonSelection(bool bInSelected);

protected:
	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void HandleConfirmButtonPressed();

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void HandleConfirmButtonReleased();

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void HandleConfirmButtonHovered();

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void HandleConfirmButtonUnhovered();

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void HandleConfirmButtonClicked();

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void HandleConfirmButtonDoubleClicked();

	UFUNCTION(BlueprintNativeEvent)
	WIDGETGROUPGENERATION_API void HandleConfirmButtonSelection(bool bInSelected);

private:
	UPROPERTY()
	TWeakObjectPtr<UGenericButtonCollection> ButtonCollection = nullptr;

	UPROPERTY()
	TWeakObjectPtr<UGenericButtonGroup> ButtonGroup = nullptr;

private:
	FButtonConfirmEvent ConfirmButtonPressedEvent;
	FButtonConfirmEvent ConfirmButtonReleasedEvent;
	FButtonConfirmEvent ConfirmButtonHoveredEvent;
	FButtonConfirmEvent ConfirmButtonUnhoveredEvent;
	FButtonConfirmEvent ConfirmButtonClickedEvent;
	FButtonConfirmEvent ConfirmButtonDoubleClickedEvent;
	FButtonSelectionConfirmEvent ConfirmSelectionChangedEvent;
};
