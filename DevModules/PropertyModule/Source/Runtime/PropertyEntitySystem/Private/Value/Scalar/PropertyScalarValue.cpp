// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/Scalar/PropertyScalarValue.h"

#include "Base/PropertyDataSource.h"

#define LOCTEXT_NAMESPACE "UPropertyScalarValue"

FPropertyScalarFormatFunction FPropertyScalarFormat::FormatAsDigits(int32 IntegralDigits, int32 FractionalDigit)
{
	return FPropertyScalarFormatFunction([IntegralDigits, FractionalDigit](double SourceValue, double NormalizedValue)
		{
			return FText::AsNumber(SourceValue, GetNumberFormattingOptions(IntegralDigits, FractionalDigit));
		}
	);
}

FPropertyScalarFormatFunction FPropertyScalarFormat::FormatAsPercent(int32 FractionalDigit)
{
	static FText PercentFormat = LOCTEXT("PercentFormat", "{0}%");

	return FPropertyScalarFormatFunction([FractionalDigit](double SourceValue, double NormalizedValue)
		{
			const FNumberFormattingOptions* FormattingOptions = GetNumberFormattingOptions(1, FractionalDigit);
			const double NormalizedValueToPercent = FMath::RoundHalfFromZero(100 * FMath::Pow(10, (float)FractionalDigit) * NormalizedValue);
			return FText::Format(PercentFormat, FText::AsNumber(NormalizedValueToPercent / FMath::Pow(10, (float)FractionalDigit), FormattingOptions));
		}
	);
}

FNumberFormattingOptions* FPropertyScalarFormat::GetNumberFormattingOptions(int32 IntegralDigits, int32 FractionalDigits)
{
	FNumberFormattingOptions* FormattingOptions = new FNumberFormattingOptions();
	FormattingOptions->MinimumIntegralDigits = IntegralDigits;
	FormattingOptions->MinimumFractionalDigits = FractionalDigits;
	FormattingOptions->MaximumFractionalDigits = FractionalDigits;
	return FormattingOptions;
}

void UPropertyScalarValue::Startup()
{
	Getter->Startup(Source, FSimpleDelegate::CreateUObject(this, &ThisClass::OnDataSourcesReady));
}

void UPropertyScalarValue::OnInitialized()
{
	Super::OnInitialized();
	StoreToInitial();

#if !UE_BUILD_SHIPPING
	ensureAlways(Getter);
	ensureAlwaysMsgf(Getter->Resolve(Source), TEXT("%s: %s did not resolve, are all functions and properties valid, and are they UFunctions/UProperties? Does the getter function have no parameters?"), *GetPropertyName().ToString(), *Getter->ToString());
	ensureAlways(Setter);
	ensureAlwaysMsgf(Setter->Resolve(Source), TEXT("%s: %s did not resolve, are all functions and properties valid, and are they UFunctions/UProperties? Does the getter function have no parameters?"), *GetPropertyName().ToString(), *Getter->ToString());
#endif
}

void UPropertyScalarValue::ResetToDefault()
{
	SetValue(DefaultValue, EPropertyChangeReason::ResetToDefault);
}

void UPropertyScalarValue::StoreToInitial()
{
	InitialValue = GetValue();
}

void UPropertyScalarValue::ResetToInitial()
{
	SetValue(InitialValue, EPropertyChangeReason::ResetToInitial);
}

void UPropertyScalarValue::OnDataSourcesReady()
{
	FinishStartup();
}

void UPropertyScalarValue::SetDataSourceGetter(const TSharedRef<FPropertyDataSource>& InGetter)
{
	Getter = InGetter;
}

void UPropertyScalarValue::SetDataSourceSetter(const TSharedRef<FPropertyDataSource>& InSetter)
{
	Setter = InSetter;
}

double UPropertyScalarValue::GetDefaultValue() const
{
	return DefaultValue;
}

double UPropertyScalarValue::GetDefaultValueNormalized() const
{
	return FMath::GetMappedRangeValueClamped(GetValueRange(), TRange<double>(0, 1), GetDefaultValue());
}

void UPropertyScalarValue::SetDefaultValue(double InValue)
{
	DefaultValue = InValue;
}

double UPropertyScalarValue::GetValue() const
{
	const FString OutValue = Getter->GetValue(Source);

	double Value;
	LexFromString(Value, *OutValue);

	return Value;
}

void UPropertyScalarValue::SetValue(double InValue, EPropertyChangeReason Reason)
{
	InValue = FMath::RoundHalfFromZero(InValue / ValueStep);
	InValue = InValue * ValueStep;

	if (MinimumUIValue.IsSet())
	{
		InValue = FMath::Max(MinimumUIValue.GetValue(), InValue);
	}

	if (MaximumUIValue.IsSet())
	{
		InValue = FMath::Min(MaximumUIValue.GetValue(), InValue);
	}

	const FString StringValue = LexToString(InValue);
	Setter->SetValue(Source, StringValue);

	NotifyPropertyChanged(Reason);
}

double UPropertyScalarValue::GetValueNormalized() const
{
	return FMath::GetMappedRangeValueClamped(GetValueRange(), TRange<double>(0, 1), GetValue());
}

void UPropertyScalarValue::SetValueNormalized(double NormalizedValue)
{
	SetValue(FMath::GetMappedRangeValueClamped(TRange<double>(0, 1), GetValueRange(), NormalizedValue));
}

void UPropertyScalarValue::SetValueRangeAndStep(const TRange<double>& InRange, double InStep)
{
	SetValueRange(InRange);
	SetValueStep(InStep);
}

TRange<double> UPropertyScalarValue::GetValueRange() const
{
	return ValueRange;
}

void UPropertyScalarValue::SetValueRange(const TRange<double>& InRange)
{
	ValueRange = InRange;
}

double UPropertyScalarValue::GetValueStep() const
{
	return ValueStep;
}

double UPropertyScalarValue::GetValueStepNormalized() const
{
	const TRange<double> SourceRange = GetValueRange();
	return GetValueStep() / FMath::Abs(SourceRange.GetUpperBoundValue() - SourceRange.GetLowerBoundValue());
}

void UPropertyScalarValue::SetValueStep(double InStep)
{
	ValueStep = InStep;
}

FText UPropertyScalarValue::GetFormattedText() const
{
	const double SourceValue = GetValue();
	const double NormalizedValue = GetValueNormalized();

	return DisplayFormat(SourceValue, NormalizedValue);
}

void UPropertyScalarValue::SetFormattedText(FPropertyScalarFormatFunction InDisplayFormat)
{
	DisplayFormat = InDisplayFormat;
}

#undef LOCTEXT_NAMESPACE
