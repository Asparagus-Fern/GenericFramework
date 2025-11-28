// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyValueBase.h"
#include "MVVM/Data/Scalar/ScalarPropertyValueViewModel.h"
#include "PropertyScalarValueBase.generated.h"

class UScalarPropertyValueViewModel;

/**
 * 
 */
UCLASS(Abstract, MinimalAPI)
class UPropertyScalarValueBase : public UPropertyValueBase
{
	GENERATED_BODY()

public:
	PROPERTYSYSTEM_API virtual TSubclassOf<UPropertyViewModel> GetSupportPropertyViewModelClass() override;
	PROPERTYSYSTEM_API virtual void PostInitPropertyViewModel() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelInitialized() override;
	PROPERTYSYSTEM_API virtual void NativeOnViewModelDeinitialized() override;

protected:
	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnInitialValueChanged(double DefaultValue);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnNormalizedInitialValueChanged(double NormalizedDefaultValue);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnCurrentValueChanged(double CurrentValue);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnNormalizedCurrentValueChanged(double NormalizedCurrentValue);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnValueStepChanged(double ValueStep);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnValueRangeChanged(FVector2D ValueRange);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnIsClampValueRangeChanged(bool IsClampValueRange);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnNormalizedValueRangeChanged(FVector2D NormalizedValueRange);

	UFUNCTION(BlueprintNativeEvent)
	PROPERTYSYSTEM_API void OnIsClampInteractionRangeChanged(bool IsIsClampInteractionRange);

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
