// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MultiPropertyValueViewModel.h"
#include "NumberPropertyValueViewModel.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UNumberPropertyValueViewModel : public UMultiPropertyValueViewModel
{
	GENERATED_UCLASS_BODY()

public:
	template <typename NumberType>
	void AddNumberValue(NumberType InValue, const FText& InOptionText)
	{
		AddValueByName(LexToString(InValue), InOptionText);
	}

	template <typename NumberType>
	void RemoveNumberValue(NumberType InValue)
	{
		RemoveValueByName(LexToString(InValue));
	}

	template <typename NumberType>
	NumberType GetNumberValue()
	{
		FString ValueString = GetCurrentValueAsString();

		NumberType OutValue;
		LexFromString(OutValue, *ValueString);

		return OutValue;
	}

	template <typename NumberType>
	void SetNumberValue(NumberType InValue)
	{
		SetCurrentValueFromString(LexToString(InValue));
	}
};
