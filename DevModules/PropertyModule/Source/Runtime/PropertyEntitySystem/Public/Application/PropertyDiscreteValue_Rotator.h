// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Value/Discrete/PropertyDiscreteOptionValue.h"
#include "PropertyDiscreteValue_Rotator.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYENTITYSYSTEM_API UPropertyDiscreteValue_Rotator : public UPropertyDiscreteOptionValue
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	FRotator GetDefaultRotatorValue() const;

	UFUNCTION(BlueprintCallable)
	void SetDefaultRotatorValue(const FRotator& InValue);

	UFUNCTION(BlueprintPure)
	FRotator GetRotatorValue() const;

	UFUNCTION(BlueprintCallable)
	void SetRotatorValue(const FRotator& InValue);

	UFUNCTION(BlueprintCallable)
	void AddRotatorOption(FName InOptionName, FRotator InOptionValue, const FText& InOptionText);
};
