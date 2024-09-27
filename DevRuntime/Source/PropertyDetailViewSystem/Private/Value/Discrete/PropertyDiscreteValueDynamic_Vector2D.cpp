// Fill out your copyright notice in the Description page of Project Settings.


#include "Value/Discrete/PropertyDiscreteValueDynamic_Vector2D.h"

void UPropertyDiscreteValueDynamic_Vector2D::SetDefaultValue(const FVector2D& InValue)
{
	SetDefaultValueFromString(InValue.ToString());
}

FVector2D UPropertyDiscreteValueDynamic_Vector2D::GetValue() const
{
	FVector2D ValueVector;
	ValueVector.InitFromString(GetValueAsString());
	return ValueVector;
}

void UPropertyDiscreteValueDynamic_Vector2D::SetValue(const FVector2D& InValue)
{
	SetValueFromString(InValue.ToString());
}
