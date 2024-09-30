// Fill out your copyright notice in the Description page of Project Settings.


#include "Value/Scalar/PropertyScalarValueDynamic.h"

#include "DataSource/PropertyDataSource.h"

#define LOCTEXT_NAMESPACE "PropertyDetailViewSystem"

static FText PercentFormat = LOCTEXT("PercentFormat", "{0}%");

FSettingScalarFormatFunction UPropertyScalarValueDynamic::FormatAsInteger([](double SourceValue, double NormalizedValue)
	{
		return FText::AsNumber(SourceValue, GetNumberFormattingOptions(1, 0));
	}
);

FSettingScalarFormatFunction UPropertyScalarValueDynamic::FormatAsOneFractionalDigit([](double SourceValue, double NormalizedValue)
	{
		return FText::AsNumber(SourceValue, GetNumberFormattingOptions(1, 1));
	}
);

FSettingScalarFormatFunction UPropertyScalarValueDynamic::FormatAsTwoFractionalDigits([](double SourceValue, double NormalizedValue)
	{
		return FText::AsNumber(SourceValue, GetNumberFormattingOptions(1, 2));
	}
);

FSettingScalarFormatFunction UPropertyScalarValueDynamic::FormatAsThreeFractionalDigits([](double SourceValue, double NormalizedValue)
	{
		return FText::AsNumber(SourceValue, GetNumberFormattingOptions(1, 3));
	}
);

FSettingScalarFormatFunction UPropertyScalarValueDynamic::FormatAsPercent([](double SourceValue, double NormalizedValue)
	{
		return FText::Format(PercentFormat, (int32)FMath::RoundHalfFromZero(100.0 * NormalizedValue));
	}
);

FSettingScalarFormatFunction UPropertyScalarValueDynamic::FormatAsPercent_OneFractionalDigit([](double SourceValue, double NormalizedValue)
	{
		const FNumberFormattingOptions* FormattingOptions = GetNumberFormattingOptions(1, 1);
		const double NormalizedValueTo100_0 = FMath::RoundHalfFromZero(1000.0 * NormalizedValue);
		return FText::Format(PercentFormat, FText::AsNumber(NormalizedValueTo100_0 / 10.0, FormattingOptions));
	}
);

FNumberFormattingOptions* UPropertyScalarValueDynamic::GetNumberFormattingOptions(int32 IntegralDigits, int32 FractionalDigits)
{
	FNumberFormattingOptions* FormattingOptions = new FNumberFormattingOptions();
	FormattingOptions->MinimumIntegralDigits = IntegralDigits;
	FormattingOptions->MinimumFractionalDigits = FractionalDigits;
	FormattingOptions->MaximumFractionalDigits = FractionalDigits;
	return FormattingOptions;
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

double UPropertyScalarValueDynamic::GetValue() const
{
	const FString OutValue = Getter->GetValueAsString(Context);

	double Value;
	LexFromString(Value, *OutValue);

	return Value;
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

void UPropertyScalarValueDynamic::SetDisplayFormat(FSettingScalarFormatFunction InDisplayFormat)
{
	DisplayFormat = InDisplayFormat;
}

#undef LOCTEXT_NAMESPACE
