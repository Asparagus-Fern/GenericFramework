// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/Discrete/PropertyDiscreteValue_Vector2D.h"

FVector2D UPropertyDiscreteValue_Vector2D::GetVector2DValue() const
{
	FVector2D Vector2DValue;
	Vector2DValue.InitFromString(GetValueAsString());
	return Vector2DValue;
}

void UPropertyDiscreteValue_Vector2D::SetVector2DValue(const FVector2D& InValue)
{
	SetValueFromString(InValue.ToString());
}

FVector2D UPropertyDiscreteValue_Vector2D::GetDefaultVector2DValue() const
{
	FVector2D Vector2DValue;
	Vector2DValue.InitFromString(GetDefaultValueAsString());
	return Vector2DValue;
}

void UPropertyDiscreteValue_Vector2D::SetDefaultVector2DValue(const FVector2D& InValue)
{
	SetDefaultValueFromString(InValue.ToString());
}
