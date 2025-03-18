// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Value/Discrete/PropertyDiscreteOptionValue.h"
#include "PropertyDiscreteValue_String.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYENTITYSYSTEM_API UPropertyDiscreteValue_String : public UPropertyDiscreteOptionValue
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	FString GetDefaultStringValue() const;

	UFUNCTION(BlueprintCallable)
	void SetDefaultStringValue(FString InValue);

	UFUNCTION(BlueprintPure)
	FString GetStringValue() const;

	UFUNCTION(BlueprintCallable)
	void SetStringValue(FString InValue);

	UFUNCTION(BlueprintCallable)
	void AddStringOption(FName InOptionName, FString InOptionValue, const FText& InOptionText);
};
