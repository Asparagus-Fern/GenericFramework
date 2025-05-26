// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Number.generated.h"

/**
 * 数字类型属性
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyDiscreteValue_Number : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	template <typename NumberType>
	NumberType GetNumberValue() const
	{
		const FString ValueString = GetValueAsString();

		NumberType OutValue;
		LexFromString(OutValue, *ValueString);

		return OutValue;
	}

	template <typename NumberType>
	void SetNumberValue(NumberType InValue)
	{
		SetValueFromString(LexToString(InValue));
	}

	template <typename NumberType>
	NumberType GetDefaultNumberValue() const
	{
		const FString ValueString = GetDefaultValueAsString();

		NumberType OutValue;
		LexFromString(OutValue, *ValueString);

		return OutValue;
	}
	
	template <typename NumberType>
	void SetDefaultNumberValue(NumberType InValue)
	{
		SetDefaultValueFromString(LexToString(InValue));
	}

	template <typename NumberType>
	void AddNumberOption(NumberType InValue, const FText& InOptionText)
	{
		AddOption(LexToString(InValue), InOptionText);
	}

	template <typename NumberType>
	void RemoveNumberOption(NumberType InValue)
	{
		RemoveOption(LexToString(InValue));
	}
};
