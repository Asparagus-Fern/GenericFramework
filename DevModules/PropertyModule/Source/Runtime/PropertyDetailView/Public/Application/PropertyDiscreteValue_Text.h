// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Value/Discrete/PropertyDiscreteOptionValue.h"
#include "PropertyDiscreteValue_Text.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEW_API UPropertyDiscreteValue_Text : public UPropertyDiscreteOptionValue
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
