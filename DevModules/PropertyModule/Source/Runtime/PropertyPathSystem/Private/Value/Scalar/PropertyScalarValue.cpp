// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Value/Scalar/PropertyScalarValue.h"

#include "Base/PropertyDataSource.h"

#define LOCTEXT_NAMESPACE "PropertyDetailViewSystem"

/* ==================== FPropertyScalarFormat ==================== */

static FText PercentFormat = LOCTEXT("PercentFormat", "{0}%");

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
	return FPropertyScalarFormatFunction([FractionalDigit](double SourceValue, double NormalizedValue)
		{
			const FNumberFormattingOptions* FormattingOptions = GetNumberFormattingOptions(1, FractionalDigit);
			const double NormalizedValueToPercent = FMath::RoundHalfFromZero(100 * FMath::Pow(10, (float)FractionalDigit) * NormalizedValue);
			return FText::Format(PercentFormat, FText::AsNumber(NormalizedValueToPercent / FMath::Pow(10, (float)FractionalDigit), FormattingOptions));
		}
	);
}

FNumberFormattingOptions* FPropertyScalarFormat::GetNumberFormattingOptions(const int32 IntegralDigits, const int32 FractionalDigits)
{
	FNumberFormattingOptions* FormattingOptions = new FNumberFormattingOptions();
	FormattingOptions->MinimumIntegralDigits = IntegralDigits;
	FormattingOptions->MinimumFractionalDigits = FractionalDigits;
	FormattingOptions->MaximumFractionalDigits = FractionalDigits;
	return FormattingOptions;
}

/* ==================== UPropertyScalarValue ==================== */

void UPropertyScalarValue::OnInitialized()
{
#if !UE_BUILD_SHIPPING
	ensureAlways(Getter);
	ensureAlwaysMsgf(Getter->Resolve(Context), TEXT("%s: %s did not resolve, are all functions and properties valid, and are they UFunctions/UProperties? Does the getter function have no parameters?"), *GetPropertyName().ToString(), *Getter->ToString());
	ensureAlways(Setter);
	ensureAlwaysMsgf(Setter->Resolve(Context), TEXT("%s: %s did not resolve, are all functions and properties valid, and are they UFunctions/UProperties? Does the getter function have no parameters?"), *GetPropertyName().ToString(), *Getter->ToString());
#endif

	Super::OnInitialized();

	StoreInitial();
}

void UPropertyScalarValue::Startup()
{
	Getter->Startup(Context, FSimpleDelegate::CreateUObject(this, &ThisClass::OnDataSourcesReady));
}

void UPropertyScalarValue::OnDataSourcesReady()
{
	StartupComplete();
}

void UPropertyScalarValue::StoreInitial()
{
	InitialValue = GetValue();
}

void UPropertyScalarValue::ResetToInitial()
{
	SetValue(InitialValue, EPropertyChangeReason::RestoreToInitial);
}

void UPropertyScalarValue::ResetToDefault()
{
	if (DefaultValue.IsSet())
	{
		SetValue(DefaultValue.GetValue(), EPropertyChangeReason::ResetToDefault);
	}
}

double UPropertyScalarValue::GetValue() const
{
	const FString OutValue = Getter->GetValueAsString(Context);

	double Value;
	LexFromString(Value, *OutValue);

	return Value;
}

void UPropertyScalarValue::SetValue(double InValue, EPropertyChangeReason Reason)
{
	InValue = FMath::RoundHalfFromZero(InValue / SourceStep);
	InValue = InValue * SourceStep;

	if (Minimum.IsSet())
	{
		InValue = FMath::Max(Minimum.GetValue(), InValue);
	}

	if (Maximum.IsSet())
	{
		InValue = FMath::Min(Maximum.GetValue(), InValue);
	}

	const FString StringValue = LexToString(InValue);
	Setter->SetValueByString(Context, StringValue);

	NotifyPropertyChanged(Reason);
}

FText UPropertyScalarValue::GetFormattedText() const
{
	const double SourceValue = GetValue();
	const double NormalizedValue = GetValueNormalized();

	return DisplayFormat(SourceValue, NormalizedValue);
}

FPropertyScalarFormatFunction UPropertyScalarValue::GetDisplayFormat()
{
	return DisplayFormat;
}

void UPropertyScalarValue::SetDisplayFormat(const FPropertyScalarFormatFunction& InDisplayFormat)
{
	DisplayFormat = InDisplayFormat;
}

#undef LOCTEXT_NAMESPACE
