// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "MultiPropertyValueViewModel.h"
#include "EnumPropertyValueViewModel.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UEnumPropertyValueViewModel : public UMultiPropertyValueViewModel
{
	GENERATED_UCLASS_BODY()

public:
	template <typename EnumType>
	void AddEnumValue(EnumType InEnumValue, const FText& InOptionText)
	{
		const FString StringValue = StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue);
		AddValueByName(StringValue, InOptionText);
	}

	template <typename EnumType>
	void RemoveEnumValue(EnumType InEnumValue)
	{
		const FString StringValue = StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue);
		RemoveValueByName(StringValue);
	}

	template <typename EnumType>
	EnumType GetEnumValue()
	{
		const FString Value = GetCurrentValueAsString();
		return (EnumType)StaticEnum<EnumType>()->GetValueByNameString(Value);
	}

	template <typename EnumType>
	void SetEnumValue(EnumType InEnumValue)
	{
		const FString StringValue = StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue);
		SetCurrentValueFromString(StringValue);
	}
};
