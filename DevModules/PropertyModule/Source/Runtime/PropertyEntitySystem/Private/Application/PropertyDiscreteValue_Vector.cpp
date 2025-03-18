// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/PropertyDiscreteValue_Vector.h"

FVector UPropertyDiscreteValue_Vector::GetDefaultVectorValue() const
{
	FVector ValueVector;
	ValueVector.InitFromString(GetDefaultValue());
	return ValueVector;
}

void UPropertyDiscreteValue_Vector::SetDefaultVectorValue(const FVector& InValue)
{
	SetDefaultValue(InValue.ToString());
}

FVector UPropertyDiscreteValue_Vector::GetVectorValue() const
{
	FVector ValueVector;
	ValueVector.InitFromString(GetValue());
	return ValueVector;
}

void UPropertyDiscreteValue_Vector::SetVectorValue(const FVector& InValue)
{
	SetValue(InValue.ToString());
}

void UPropertyDiscreteValue_Vector::AddVectorOption(FName InOptionName, FVector InOptionValue, const FText& InOptionText)
{
	AddOption(InOptionName, InOptionValue.ToString(), InOptionText);
}
