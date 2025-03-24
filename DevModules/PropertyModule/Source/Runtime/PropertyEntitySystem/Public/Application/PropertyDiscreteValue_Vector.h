// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Value/Discrete/PropertyDiscreteOptionValue.h"
#include "PropertyDiscreteValue_Vector.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYENTITYSYSTEM_API UPropertyDiscreteValue_Vector : public UPropertyDiscreteOptionValue
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	FVector GetDefaultVectorValue() const;

	UFUNCTION(BlueprintCallable)
	void SetDefaultVectorValue(const FVector& InValue);

	UFUNCTION(BlueprintPure)
	FVector GetVectorValue() const;

	UFUNCTION(BlueprintCallable)
	void SetVectorValue(const FVector& InValue);

	UFUNCTION(BlueprintCallable)
	void AddVectorOption(FName InOptionName, FVector InOptionValue, const FText& InOptionText);
};
