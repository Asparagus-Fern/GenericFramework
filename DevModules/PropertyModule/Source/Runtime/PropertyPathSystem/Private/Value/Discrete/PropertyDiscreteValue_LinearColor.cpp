// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/Discrete/PropertyDiscreteValue_LinearColor.h"

FLinearColor UPropertyDiscreteValue_LinearColor::GetLinearColorValue() const
{
	FLinearColor ColorValue;
	ColorValue.InitFromString(GetValueAsString());
	return ColorValue;
}

void UPropertyDiscreteValue_LinearColor::SetLinearColorValue(const FLinearColor InValue)
{
	SetValueFromString(InValue.ToString());
}

FLinearColor UPropertyDiscreteValue_LinearColor::GetDefaultLinearColorValue() const
{
	FLinearColor ColorValue;
	ColorValue.InitFromString(GetDefaultValueAsString());
	return ColorValue;
}

void UPropertyDiscreteValue_LinearColor::SetDefaultLinearColorValue(const FLinearColor InValue)
{
	SetDefaultValueFromString(InValue.ToString());
}