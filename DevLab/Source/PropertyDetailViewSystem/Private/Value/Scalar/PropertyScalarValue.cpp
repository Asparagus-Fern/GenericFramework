// Fill out your copyright notice in the Description page of Project Settings.

#include "Value/Scalar/PropertyScalarValue.h"

void UPropertyScalarValue::OnInitialized()
{
	Super::OnInitialized();

	StoreInitial();
}

void UPropertyScalarValue::SetValueNormalized(double NormalizedValue)
{
	SetValue(FMath::GetMappedRangeValueClamped(TRange<double>(0, 1), GetSourceRange(), NormalizedValue));
}

double UPropertyScalarValue::GetValueNormalized() const
{
	return FMath::GetMappedRangeValueClamped(GetSourceRange(), TRange<double>(0, 1), GetValue());
}

TOptional<double> UPropertyScalarValue::GetDefaultValueNormalized() const
{
	TOptional<double> DefaultValue = GetDefaultValue();
	if (DefaultValue.IsSet())
	{
		return FMath::GetMappedRangeValueClamped(GetSourceRange(), TRange<double>(0, 1), DefaultValue.GetValue());
	}
	return TOptional<double>();
}

double UPropertyScalarValue::GetNormalizedStepSize() const
{
	const TRange<double> SourceRange = GetSourceRange();
	return GetSourceStep() / FMath::Abs(SourceRange.GetUpperBoundValue() - SourceRange.GetLowerBoundValue());
}
