// Fill out your copyright notice in the Description page of Project Settings.


#include "Value/Scalar/PropertyScalarValueDynamic.h"

#include "DataSource/PropertyDataSource.h"

#define LOCTEXT_NAMESPACE "PropertyDetailViewSystem"

static FText PercentFormat = LOCTEXT("PercentFormat", "{0}%");

FPropertyScalarFormatFunction UPropertyScalarValueDynamic::FormatAsDigits(int32 IntegralDigits, int32 FractionalDigit)
{
	return FPropertyScalarFormatFunction([IntegralDigits, FractionalDigit](double SourceValue, double NormalizedValue)
		{
			return FText::AsNumber(SourceValue, GetNumberFormattingOptions(IntegralDigits, FractionalDigit));
		}
	);
}

FPropertyScalarFormatFunction UPropertyScalarValueDynamic::FormatAsPercent(int32 FractionalDigit)
{
	return FPropertyScalarFormatFunction([FractionalDigit](double SourceValue, double NormalizedValue)
		{
			const FNumberFormattingOptions* FormattingOptions = GetNumberFormattingOptions(1, FractionalDigit);
			const double NormalizedValueToPercent = FMath::RoundHalfFromZero(100 * FMath::Pow(10, (float)FractionalDigit) * NormalizedValue);
			return FText::Format(PercentFormat, FText::AsNumber(NormalizedValueToPercent / FMath::Pow(10, (float)FractionalDigit), FormattingOptions));
		}
	);
}

FNumberFormattingOptions* UPropertyScalarValueDynamic::GetNumberFormattingOptions(int32 IntegralDigits, int32 FractionalDigits)
{
	FNumberFormattingOptions* FormattingOptions = new FNumberFormattingOptions();
	FormattingOptions->MinimumIntegralDigits = IntegralDigits;
	FormattingOptions->MinimumFractionalDigits = FractionalDigits;
	FormattingOptions->MaximumFractionalDigits = FractionalDigits;
	return FormattingOptions;
}

void UPropertyScalarValueDynamic::OnInitialized()
{
#if !UE_BUILD_SHIPPING
	ensureAlways(Getter);
	ensureAlwaysMsgf(Getter->Resolve(Context), TEXT("%s: %s did not resolve, are all functions and properties valid, and are they UFunctions/UProperties? Does the getter function have no parameters?"), *GetPropertyName().ToString(), *Getter->ToString());
	ensureAlways(Setter);
	ensureAlwaysMsgf(Setter->Resolve(Context), TEXT("%s: %s did not resolve, are all functions and properties valid, and are they UFunctions/UProperties? Does the getter function have no parameters?"), *GetPropertyName().ToString(), *Getter->ToString());
#endif

	Super::OnInitialized();
}

void UPropertyScalarValueDynamic::Startup()
{
	Getter->Startup(Context, FSimpleDelegate::CreateUObject(this, &ThisClass::OnDataSourcesReady));
}

void UPropertyScalarValueDynamic::OnDataSourcesReady()
{
	StartupComplete();
}

void UPropertyScalarValueDynamic::StoreInitial()
{
	InitialValue = GetValue();
}

void UPropertyScalarValueDynamic::ResetToDefault()
{
	if (DefaultValue.IsSet())
	{
		SetValue(DefaultValue.GetValue(), EPropertyChangeReason::ResetToDefault);
	}
}

void UPropertyScalarValueDynamic::RestoreToInitial()
{
	SetValue(InitialValue, EPropertyChangeReason::RestoreToInitial);
}

TOptional<double> UPropertyScalarValueDynamic::GetDefaultValue() const
{
	return DefaultValue;
}

void UPropertyScalarValueDynamic::SetDefaultValue(double InValue)
{
	DefaultValue = InValue;
}

double UPropertyScalarValueDynamic::GetValue() const
{
	const FString OutValue = Getter->GetValueAsString(Context);

	double Value;
	LexFromString(Value, *OutValue);

	return Value;
}

void UPropertyScalarValueDynamic::SetValue(double InValue, EPropertyChangeReason Reason)
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
	Setter->SetValue(Context, StringValue);

	NotifyPropertyChanged(Reason);
}

TRange<double> UPropertyScalarValueDynamic::GetSourceRange() const
{
	return SourceRange;
}

double UPropertyScalarValueDynamic::GetSourceStep() const
{
	return SourceStep;
}

FText UPropertyScalarValueDynamic::GetFormattedText() const
{
	const double SourceValue = GetValue();
	const double NormalizedValue = GetValueNormalized();

	return DisplayFormat(SourceValue, NormalizedValue);
}

void UPropertyScalarValueDynamic::SetDataSourceGetter(const TSharedRef<FPropertyDataSource>& InGetter)
{
	Getter = InGetter;
}

void UPropertyScalarValueDynamic::SetDataSourceSetter(const TSharedRef<FPropertyDataSource>& InSetter)
{
	Setter = InSetter;
}

void UPropertyScalarValueDynamic::SetMinimumLimit(const TOptional<double>& InMinimum)
{
	Minimum = InMinimum;
}

void UPropertyScalarValueDynamic::SetMaximumLimit(const TOptional<double>& InMaximum)
{
	Maximum = InMaximum;
}

void UPropertyScalarValueDynamic::SetSourceRangeAndStep(const TRange<double>& InRange, double InSourceStep)
{
	SourceRange = InRange;
	SourceStep = InSourceStep;
}

void UPropertyScalarValueDynamic::SetSourceRange(const TRange<double>& InRange)
{
	SourceRange = InRange;
}

void UPropertyScalarValueDynamic::SetSourceStep(double InSourceStep)
{
	SourceStep = InSourceStep;
}

void UPropertyScalarValueDynamic::SetDisplayFormat(FPropertyScalarFormatFunction InDisplayFormat)
{
	DisplayFormat = InDisplayFormat;
}

#undef LOCTEXT_NAMESPACE
