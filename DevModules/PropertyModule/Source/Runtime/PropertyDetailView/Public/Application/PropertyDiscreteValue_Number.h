// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Value/Discrete/PropertyDiscreteOptionValue.h"
#include "PropertyDiscreteValue_Number.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEW_API UPropertyDiscreteValue_Number : public UPropertyDiscreteOptionValue
{
	GENERATED_BODY()

public:
	template <typename NumberType>
	NumberType GetDefaultNumberValue()
	{
		const FString DefaultValue = GetDefaultValue();

		NumberType OutValue;
		LexFromString(OutValue, *DefaultValue);

		return OutValue;
	}

	template <typename NumberType>
	void SetDefaultNumberValue(NumberType InOptionValue)
	{
		SetDefaultValue(LexToString(InOptionValue));
	}

	template <typename NumberType>
	NumberType GetNumberValue() const
	{
		const FString ValueString = GetValue();

		NumberType OutValue;
		LexFromString(OutValue, *ValueString);

		return OutValue;
	}

	template <typename NumberType>
	void SetNumberValue(NumberType InOptionValue)
	{
		SetValue(LexToString(InOptionValue));
	}

	template <typename NumberType>
	UPropertyDiscreteOption* AddNumberOption(FName InOptionName, NumberType InOptionValue, const FText& InOptionText)
	{
		return AddOption(InOptionName, LexToString(InOptionValue), InOptionText);
	}
};
