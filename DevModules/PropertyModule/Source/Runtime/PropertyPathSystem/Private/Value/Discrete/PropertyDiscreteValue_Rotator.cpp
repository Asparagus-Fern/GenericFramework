// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/Discrete/PropertyDiscreteValue_Rotator.h"

FRotator UPropertyDiscreteValue_Rotator::GetRotatorValue() const
{
	FRotator RotatorValue;
	RotatorValue.InitFromString(GetValueAsString());
	return RotatorValue;
}

void UPropertyDiscreteValue_Rotator::SetRotatorValue(const FRotator& InValue)
{
	SetValueFromString(InValue.ToString());
}

FRotator UPropertyDiscreteValue_Rotator::GetDefaultRotatorValue() const
{
	FRotator RotatorValue;
	RotatorValue.InitFromString(GetDefaultValueAsString());
	return RotatorValue;
}

void UPropertyDiscreteValue_Rotator::SetDefaultRotatorValue(const FRotator& InValue)
{
	SetDefaultValueFromString(InValue.ToString());
}
