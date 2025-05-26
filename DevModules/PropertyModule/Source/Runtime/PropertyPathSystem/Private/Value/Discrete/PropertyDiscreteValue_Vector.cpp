// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/Discrete/PropertyDiscreteValue_Vector.h"

FVector UPropertyDiscreteValue_Vector::GetVectorValue() const
{
	FVector VectorValue;
	VectorValue.InitFromString(GetValueAsString());
	return VectorValue;
}

void UPropertyDiscreteValue_Vector::SetVectorValue(const FVector& InValue)
{
	SetValueFromString(InValue.ToString());
}

FVector UPropertyDiscreteValue_Vector::GetDefaultVectorValue() const
{
	FVector VectorValue;
	VectorValue.InitFromString(GetDefaultValueAsString());
	return VectorValue;
}

void UPropertyDiscreteValue_Vector::SetDefaultVectorValue(const FVector& InValue)
{
	SetDefaultValueFromString(InValue.ToString());
}
