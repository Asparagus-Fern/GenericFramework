// Fill out your copyright notice in the Description page of Project Settings.


#include "Value/PropertyScalarValue.h"

void UPropertyScalarValue::SetValueNormalized(double NormalizedValue)
{
	SetValue(FMath::GetMappedRangeValueClamped(TRange<double>(0, 1), GetSourceRange(), NormalizedValue));
}

double UPropertyScalarValue::GetValueNormalized() const
{
	// UFunction* Function = FindFunction("A");
	// uint8* Parms = new(FMemStack::Get(), MEM_Zeroed, Function->ParmsSize)uint8;
	// ProcessEvent(Function, Parms);
	return FMath::GetMappedRangeValueClamped(GetSourceRange(), TRange<double>(0, 1), GetValue());
}
