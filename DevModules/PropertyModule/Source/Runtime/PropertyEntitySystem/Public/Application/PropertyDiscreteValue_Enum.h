// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Value/Discrete/PropertyDiscreteOptionValue.h"
#include "PropertyDiscreteValue_Enum.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYENTITYSYSTEM_API UPropertyDiscreteValue_Enum : public UPropertyDiscreteOptionValue
{
	GENERATED_BODY()

public:
	template <typename EnumType>
	EnumType GetDefaultEnumValue()
	{
		const FString Value = GetDefaultValue();
		return (EnumType)StaticEnum<EnumType>()->GetValueByNameString(Value);
	}

	template <typename EnumType>
	void SetDefaultEnumValue(EnumType InEnumValue)
	{
		const FString StringValue = StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue);
		SetDefaultValue(StringValue);
	}

	template <typename EnumType>
	EnumType GetEnumValue() const
	{
		const FString Value = GetValue();
		return (EnumType)StaticEnum<EnumType>()->GetValueByNameString(Value);
	}

	template <typename EnumType>
	void SetEnumValue(EnumType InEnumValue)
	{
		const FString StringValue = StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue);
		SetValue(StringValue);
	}

	template <typename EnumType>
	void AddEnumOption(FName InOptionName, EnumType InEnumValue, const FText& InOptionText)
	{
		AddOption(InOptionName, StaticEnum<EnumType>()->GetNameStringByValue((int64)InEnumValue), InOptionText);
	}
};
