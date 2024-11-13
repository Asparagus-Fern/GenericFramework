// Fill out your copyright notice in the Description page of Project Settings.


#include "Value/Discrete/PropertyDiscreteValueDynamic_Vector.h"

void UPropertyDiscreteValueDynamic_Vector::SetDefaultValue(const FVector& InValue)
{
	SetDefaultValueFromString(InValue.ToString());
}

FVector UPropertyDiscreteValueDynamic_Vector::GetValue() const
{
	FVector ValueVector;
	ValueVector.InitFromString(GetValueAsString());
	return ValueVector;
}

void UPropertyDiscreteValueDynamic_Vector::SetValue(const FVector& InValue)
{
	SetValueFromString(InValue.ToString());
}
