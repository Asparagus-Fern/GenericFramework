// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UMG/PropertyValue/PropertyScalarValueBase.h"
#include "ScalarValue_SpinBox.generated.h"

class USpinBox;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UScalarValue_SpinBox : public UPropertyScalarValueBase
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual void NativeConstruct() override;
	PROPERTYSYSTEM_API virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void HandleOnSpinBoxValueChanged(float InValue);

protected:
	PROPERTYSYSTEM_API virtual void OnCurrentValueChanged_Implementation(double CurrentValue) override;
	PROPERTYSYSTEM_API virtual void OnNormalizedCurrentValueChanged_Implementation(double NormalizedCurrentValue) override;
	PROPERTYSYSTEM_API virtual void OnValueStepChanged_Implementation(double ValueStep) override;
	PROPERTYSYSTEM_API virtual void OnValueRangeChanged_Implementation(FVector2D ValueRange) override;
	PROPERTYSYSTEM_API virtual void OnNormalizedValueRangeChanged_Implementation(FVector2D NormalizedValueRange) override;
	PROPERTYSYSTEM_API virtual void OnValueInteractionRangeChanged_Implementation(FVector2D ValueInteractionRange) override;
	PROPERTYSYSTEM_API virtual void OnNormalizedValueInteractionRangeChanged_Implementation(FVector2D NormalizedValueInteractionRange) override;
	PROPERTYSYSTEM_API virtual void OnDisplayFormatChanged_Implementation(EScalarPropertyValueDisplayFormat DisplayFormat) override;

protected:
	virtual void RefreshSpinBox();
	UFUNCTION(BlueprintNativeEvent)
	void RefreshSpinBoxCustom();

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget, BlueprintProtected = true, AllowPrivateAccess = true))
	TObjectPtr<USpinBox> SpinBox_PropertyValue;
};
