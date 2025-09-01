// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertySingleValueBase.h"
#include "MVVM/Scalar/ScalarPropertyValueViewModel.h"
#include "PropertyScalarValueBase.generated.h"

class UScalarPropertyValueViewModel;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyScalarValueBase : public UPropertySingleValueBase
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual TSubclassOf<UPropertyValueViewModel> GetSupportPropertyViewModelClass() override;
	PROPERTYSYSTEM_API virtual void PostInitPropertyViewModel() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelInitialized() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelDeinitialized() override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnDefaultValueChanged(double DefaultValue);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnNormalizedDefaultValueChanged(double NormalizedDefaultValue);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnCurrentValueChanged(double CurrentValue);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnNormalizedCurrentValueChanged(double NormalizedCurrentValue);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnValueStepChanged(double ValueStep);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnValueRangeChanged(FVector2D ValueRange);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnNormalizedValueRangeChanged(FVector2D NormalizedValueRange);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnValueInteractionRangeChanged(FVector2D ValueInteractionRange);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnNormalizedValueInteractionRangeChanged(FVector2D NormalizedValueInteractionRange);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnDisplayFormatChanged(EScalarPropertyValueDisplayFormat DisplayFormat);

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UScalarPropertyValueViewModel> ScalarPropertyValueViewModel = nullptr;
};
