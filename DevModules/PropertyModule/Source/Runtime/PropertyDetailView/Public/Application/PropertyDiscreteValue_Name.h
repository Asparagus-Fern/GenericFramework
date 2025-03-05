// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Value/Discrete/PropertyDiscreteOptionValue.h"
#include "PropertyDiscreteValue_Name.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEW_API UPropertyDiscreteValue_Name : public UPropertyDiscreteOptionValue
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	FName GetDefaultNameValue() const;

	UFUNCTION(BlueprintCallable)
	void SetDefaultNameValue(FName InValue);

	UFUNCTION(BlueprintPure)
	FName GetNameValue() const;

	UFUNCTION(BlueprintCallable)
	void SetNameValue(FName InValue);

	UFUNCTION(BlueprintCallable)
	void AddNameOption(FName InOptionName, FName InOptionValue, const FText& InOptionText);
};
