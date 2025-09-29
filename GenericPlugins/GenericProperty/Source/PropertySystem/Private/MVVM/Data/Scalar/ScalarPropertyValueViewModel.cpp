// Copyright ChenTaiye 2025. All Rights Reserved.

#include "MVVM/Data/Scalar/ScalarPropertyValueViewModel.h"

FString UScalarPropertyValueViewModel::GetInitialValueAsString()
{
	return LexToString(InitialValue);
}

void UScalarPropertyValueViewModel::SetInitialValueFromString(const FString& InValue)
{
	Super::SetInitialValueFromString(InValue);

	double Value;
	LexFromString(Value, *InValue);
	SetInitialValue(Value);
}

FString UScalarPropertyValueViewModel::GetCurrentValueAsString()
{
	return LexToString(CurrentValue);
}

void UScalarPropertyValueViewModel::SetCurrentValueFromString(const FString& InValue)
{
	Super::SetCurrentValueFromString(InValue);

	double Value;
	LexFromString(Value, *InValue);
	SetCurrentValue(Value);
}

double UScalarPropertyValueViewModel::GetInitialValue() const
{
	return InitialValue;
}

void UScalarPropertyValueViewModel::SetInitialValue(double InValue)
{
	const FDoubleRange Range(ValueRange.X, ValueRange.Y);
	if (Range.Contains(InValue))
	{
		if (UE_MVVM_SET_PROPERTY_VALUE_INLINE(InitialValue, InValue))
		{
			SetNormalizedInitialValue(GetNormalizedInitialValue());
		}
	}
}

double UScalarPropertyValueViewModel::GetNormalizedInitialValue() const
{
	return NormalizeValue(NormalizedInitialValue);
}

void UScalarPropertyValueViewModel::SetNormalizedInitialValue(double InValue)
{
	const FDoubleRange Range(0.f, 1.f);
	if (Range.Contains(InValue))
	{
		UE_MVVM_SET_PROPERTY_VALUE_INLINE(NormalizedInitialValue, InValue);
	}
}

double UScalarPropertyValueViewModel::GetCurrentValue() const
{
	return CurrentValue;
}

void UScalarPropertyValueViewModel::SetCurrentValue(double InValue)
{
	const FDoubleRange Range(ValueRange.X, ValueRange.Y);
	if (Range.Contains(InValue) && CurrentValue != InValue)
	{
		PrePropertyChanged();
		CurrentValue = InValue;
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CurrentValue);
		SetNormalizedCurrentValue(GetNormalizedCurrentValue());
		PostPropertyChanged();
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
	if (UE_MVVM_SET_PROPERTY_VALUE_INLINE(ValueRange, InValueRange))
	{
		SetNormalizedValueRange(GetNormalizedValueRange());
	}
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
	if (UE_MVVM_SET_PROPERTY_VALUE_INLINE(ValueInteractionRange, InValueRange))
	{
		SetNormalizedValueRange(GetNormalizedValueInteractionRange());
	}
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
