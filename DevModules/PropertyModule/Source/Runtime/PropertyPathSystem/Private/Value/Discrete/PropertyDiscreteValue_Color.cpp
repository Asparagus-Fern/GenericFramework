// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/Discrete/PropertyDiscreteValue_Color.h"

FColor UPropertyDiscreteValue_Color::GetColorValue() const
{
	FColor ColorValue;
	ColorValue.InitFromString(GetValueAsString());
	return ColorValue;
}

void UPropertyDiscreteValue_Color::SetColorValue(const FColor InValue)
{
	SetValueFromString(InValue.ToString());
}

FColor UPropertyDiscreteValue_Color::GetDefaultColorValue() const
{
	FColor ColorValue;
	ColorValue.InitFromString(GetDefaultValueAsString());
	return ColorValue;
}

void UPropertyDiscreteValue_Color::SetDefaultColorValue(const FColor InValue)
{
	SetDefaultValueFromString(InValue.ToString());
}
