// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyListEntry.h"
#include "PropertyListEntry_Scalar.generated.h"

class UPropertyScalarValue;
class USlider;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyListEntry_Scalar : public UPropertyListEntry
{
	GENERATED_BODY()

public:
	PROPERTYPATHSYSTEM_API virtual void SetPropertyEntity(UPropertyEntity* InProperty) override;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeOnEntryReleased() override;
	virtual void OnPropertyChanged(UPropertyEntity* InProperty, EPropertyChangeReason Reson) override;
	virtual void RefreshEditableState(FPropertyEditableState InEditableState) override;

	virtual void Refresh();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnValueChanged(float Value);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDefaultValueChanged(float DefaultValue);

protected:
	UPROPERTY()
	TObjectPtr<UPropertyScalarValue> ScalarProperty;

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UPanelWidget> Panel_Value;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> Text_PropertyValue;
};
