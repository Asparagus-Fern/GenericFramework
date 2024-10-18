// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValueDynamic.h"
#include "PropertyDiscreteValueDynamic_Number.generated.h"

/**
 * 数字类型属性
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyDiscreteValueDynamic_Number : public UPropertyDiscreteValueDynamic
{
	GENERATED_BODY()

public:
	template <typename NumberType>
	void SetDefaultValue(NumberType InValue)
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

	template <typename NumberType>
	NumberType GetValue() const
	{
		const FString ValueString = GetValueAsString();

		NumberType OutValue;
		LexFromString(OutValue, *ValueString);

		return OutValue;
	}

	template <typename NumberType>
	void SetValue(NumberType InValue)
	{
		SetValueFromString(LexToString(InValue));
	}
};
