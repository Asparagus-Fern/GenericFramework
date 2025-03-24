// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Value/Discrete/PropertyDiscreteOptionValue.h"
#include "PropertyDiscreteValue_Text.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYENTITYSYSTEM_API UPropertyDiscreteValue_Text : public UPropertyDiscreteOptionValue
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	FText GetDefaultTextValue() const;

	UFUNCTION(BlueprintCallable)
	void SetDefaultTextValue(FText InValue);

	UFUNCTION(BlueprintPure)
	FText GetTextValue() const;

	UFUNCTION(BlueprintCallable)
	void SetTextValue(FText InValue);

	UFUNCTION(BlueprintCallable)
	void AddTextOption(FName InOptionName, FText InOptionValue, const FText& InOptionText);
};
