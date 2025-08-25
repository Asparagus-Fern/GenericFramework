// Copyright ChenTaiye 2025. All Rights Reserved.

#include "MVVM/Scalar/ScalarPropertyValueViewModel.h"

double UScalarPropertyValueViewModel::GetDefaultValue() const
{
	return DefaultValue;
}

void UScalarPropertyValueViewModel::SetDefaultValue(double InValue)
{
	const FDoubleRange Range(ValueRange.X, ValueRange.Y);
	if (Range.Contains(InValue))
	{
		UE_MVVM_SET_PROPERTY_VALUE_INLINE(DefaultValue, InValue);
		SetNormalizedDefaultValue(GetNormalizedDefaultValue());
	}
}

double UScalarPropertyValueViewModel::GetNormalizedDefaultValue() const
{
	return NormalizeValue(NormalizedDefaultValue);
}

void UScalarPropertyValueViewModel::SetNormalizedDefaultValue(double InValue)
{
	const FDoubleRange Range(0.f, 1.f);
	if (Range.Contains(InValue))
	{
		UE_MVVM_SET_PROPERTY_VALUE_INLINE(NormalizedDefaultValue, InValue);
	}
}

double UScalarPropertyValueViewModel::GetCurrentValue() const
{
	return CurrentValue;
}

void UScalarPropertyValueViewModel::SetCurrentValue(double InValue)
{
	const FDoubleRange Range(ValueRange.X, ValueRange.Y);
	if (Range.Contains(InValue))
	{
		UE_MVVM_SET_PROPERTY_VALUE_INLINE(CurrentValue, InValue);
		SetNormalizedCurrentValue(GetNormalizedCurrentValue());
	}
}

double UScalarPropertyValueViewModel::GetNormalizedCurrentValue() const
{
	return NormalizeValue(NormalizedCurrentValue);
}

void UScalarPropertyValueViewModel::SetNormalizedCurrentValue(double InValue)
{
	const FDoubleRange Range(0.f, 1.f);
	if (Range.Contains(InValue))
	{
		UE_MVVM_SET_PROPERTY_VALUE_INLINE(NormalizedCurrentValue, InValue);
	}
}

double UScalarPropertyValueViewModel::GetValueStep() const
{
	return ValueStep;
}

void UScalarPropertyValueViewModel::SetValueStep(double InValue)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(ValueStep, InValue);
}

FVector2D UScalarPropertyValueViewModel::GetValueRange() const
{
	return ValueRange;
}

void UScalarPropertyValueViewModel::SetValueRange(FVector2D InValueRange)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(ValueRange, InValueRange);
	SetNormalizedValueRange(GetNormalizedValueRange());
}

FVector2D UScalarPropertyValueViewModel::GetNormalizedValueRange() const
{
	return NormalizeRange(ValueRange);
}

void UScalarPropertyValueViewModel::SetNormalizedValueRange(FVector2D InValueRange)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(NormalizedValueRange, InValueRange);
}

FVector2D UScalarPropertyValueViewModel::GetValueInteractionRange() const
{
	return ValueInteractionRange;
}

void UScalarPropertyValueViewModel::SetValueInteractionRange(FVector2D InValueRange)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(ValueInteractionRange, InValueRange);
	SetNormalizedValueRange(GetNormalizedValueInteractionRange());
}

FVector2D UScalarPropertyValueViewModel::GetNormalizedValueInteractionRange() const
{
	return NormalizeRange(ValueInteractionRange);
}

void UScalarPropertyValueViewModel::SetNormalizedValueInteractionRange(FVector2D InValueRange)
{
	UE_MVVM_SET_PROPERTY_VALUE_INLINE(NormalizedValueInteractionRange, InValueRange);
}

double UScalarPropertyValueViewModel::NormalizeValue(double InValue) const
{
	return FMath::GetMappedRangeValueClamped(ValueRange, FVector2D(0.f, 1.f), InValue);
}

FVector2D UScalarPropertyValueViewModel::NormalizeRange(FVector2D InValue) const
{
	return FVector2D
	(
		FMath::GetMappedRangeValueClamped(ValueRange, FVector2D(0.f, 1.f), InValue.X),
		FMath::GetMappedRangeValueClamped(ValueRange, FVector2D(0.f, 1.f), InValue.Y)
	);
}
