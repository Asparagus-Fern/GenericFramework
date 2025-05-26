// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyDiscreteValue.h"
#include "PropertyDiscreteValue_Enum.generated.h"

/**
 * 枚举类型属性
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyDiscreteValue_Enum : public UPropertyDiscreteValue
{
	GENERATED_BODY()

public:
	template <typename EnumType>
	EnumType GetEnumValue() const
	{
		const FString Value = GetValueAsString();
		return (EnumType)StaticEnum<EnumType>()->GetValueByNameString(Value);
	}

	template <typename EnumType>
	void SetEnumValue(EnumType InEnumValue)
	{
		const FString StringValue = StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue);
		SetValueFromString(StringValue);
	}

	template <typename EnumType>
	EnumType GetDefaultEnumValue() const
	{
		const FString Value = GetDefaultValueAsString();
		return (EnumType)StaticEnum<EnumType>()->GetValueByNameString(Value);
	}

	template <typename EnumType>
	void SetDefaultEnumValue(EnumType InEnumValue)
	{
		const FString StringValue = StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue);
		SetDefaultValueFromString(StringValue);
	}

	template <typename EnumType>
	void AddEnumOption(EnumType InEnumValue, const FText& InOptionText)
	{
		const FString StringValue = StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue);
		AddOption(StringValue, InOptionText);
	}

	template <typename EnumType>
	void RemoveEnumOption(EnumType InEnumValue)
	{
		const FString StringValue = StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue);
		RemoveOption(StringValue);
	}
};
