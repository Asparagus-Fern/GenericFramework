// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/Discrete/PropertyDiscreteValue_Name.h"

FName UPropertyDiscreteValue_Name::GetNameValue() const
{
	return FName(GetValueAsString());
}

void UPropertyDiscreteValue_Name::SetNameValue(const FName InValue)
{
	SetValueFromString(InValue.ToString());
}

FName UPropertyDiscreteValue_Name::GetDefaultNameValue() const
{
	return FName(GetDefaultValueAsString());
}

void UPropertyDiscreteValue_Name::SetDefaultNameValue(const FName InValue)
{
	SetDefaultValueFromString(InValue.ToString());
}
