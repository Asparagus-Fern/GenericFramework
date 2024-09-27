// Fill out your copyright notice in the Description page of Project Settings.


#include "Value/Discrete/PropertyDiscreteValueDynamic_Rotator.h"

void UPropertyDiscreteValueDynamic_Rotator::SetDefaultValue(const FRotator& InValue)
{
	SetDefaultValueFromString(InValue.ToString());
}

FRotator UPropertyDiscreteValueDynamic_Rotator::GetValue() const
{
	FRotator ValueVector;
	ValueVector.InitFromString(GetValueAsString());
	return ValueVector;
}

void UPropertyDiscreteValueDynamic_Rotator::SetValue(const FRotator& InValue)
{
	SetValueFromString(InValue.ToString());
}
