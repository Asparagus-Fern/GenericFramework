// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Value/Discrete/PropertyDiscreteOptionValue.h"
#include "PropertyDiscreteValue_Bool.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYENTITYSYSTEM_API UPropertyDiscreteValue_Bool : public UPropertyDiscreteOptionValue
{
	GENERATED_BODY()

public:
	UPropertyDiscreteValue_Bool();

public:
	UFUNCTION(BlueprintCallable)
	void SetDefaultValue(bool InValue);

	UFUNCTION(BlueprintCallable)
	void SetTrueText(const FText& InText);

	UFUNCTION(BlueprintCallable)
	void SetFalseText(const FText& InText);

	UFUNCTION(BlueprintCallable)
	void SetTrueDescriptionText(const FText& InText);

	UFUNCTION(BlueprintCallable)
	void SetFalseDescriptionText(const FText& InText);
};
