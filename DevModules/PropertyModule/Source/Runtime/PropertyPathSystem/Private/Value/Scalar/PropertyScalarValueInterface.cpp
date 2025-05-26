// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/Scalar/PropertyScalarValueInterface.h"

void FPropertyScalarValueInterface::SetDataSourceGetter(const TSharedRef<FPropertyDataSource>& InGetter)
{
	Getter = InGetter;
}

void FPropertyScalarValueInterface::SetDataSourceSetter(const TSharedRef<FPropertyDataSource>& InSetter)
{
	Setter = InSetter;
}

double FPropertyScalarValueInterface::GetValueNormalized() const
{
	return FMath::GetMappedRangeValueClamped(GetSourceRange(), TRange<double>(0, 1), GetValue());
}

void FPropertyScalarValueInterface::SetValueNormalized(const double InNormalizedValue)
{
	SetValue(FMath::GetMappedRangeValueClamped(TRange<double>(0, 1), GetSourceRange(), InNormalizedValue));
}

TOptional<double> FPropertyScalarValueInterface::GetDefaultValue() const
{
	return DefaultValue;
}

void FPropertyScalarValueInterface::SetDefaultValue(const double InValue)
{
	DefaultValue = InValue;
}

TOptional<double> FPropertyScalarValueInterface::GetDefaultValueNormalized() const
{
	TOptional<double> LocalDefaultValue = GetDefaultValue();
	if (LocalDefaultValue.IsSet())
	{
		return FMath::GetMappedRangeValueClamped(GetSourceRange(), TRange<double>(0, 1), LocalDefaultValue.GetValue());
	}
	return TOptional<double>();
}

void FPropertyScalarValueInterface::SetDefaultValueNormalized(const double InNormalizedValue)
{
	SetDefaultValue(FMath::GetMappedRangeValueClamped(TRange<double>(0, 1), GetSourceRange(), InNormalizedValue));
}

TRange<double> FPropertyScalarValueInterface::GetSourceRange() const
{
	return SourceRange;
}

void FPropertyScalarValueInterface::SetSourceRange(const TRange<double> InRange)
{
	SourceRange = InRange;
}

double FPropertyScalarValueInterface::GetSourceStep() const
{
	return SourceStep;
}

void FPropertyScalarValueInterface::SetSourceStep(const double InStep)
{
	SourceStep = InStep;
}

double FPropertyScalarValueInterface::GetSourceStepNormalized() const
{
	const TRange<double> LocalSourceRange = GetSourceRange();
	return GetSourceStep() / FMath::Abs(LocalSourceRange.GetUpperBoundValue() - LocalSourceRange.GetLowerBoundValue());
}

void FPropertyScalarValueInterface::SetSourceRangeAndStep(const TRange<double>& InRange, const double InStep)
{
	SetSourceRange(InRange);
	SetSourceStep(InStep);
}

TOptional<double> FPropertyScalarValueInterface::GetMinimumLimit()
{
	return Minimum;
}

void FPropertyScalarValueInterface::SetMinimumLimit(const TOptional<double>& InMinimum)
{
	Minimum = InMinimum;
}

TOptional<double> FPropertyScalarValueInterface::GetMaximumLimit()
{
	return Maximum;
}

void FPropertyScalarValueInterface::SetMaximumLimit(const TOptional<double>& InMaximum)
{
	Maximum = InMaximum;
}
