// Fill out your copyright notice in the Description page of Project Settings.


#include "Value/Scalar/PropertyScalarValueDynamic.h"

#include "Base/PropertyDataSource.h"

void UPropertyScalarValueDynamic::Startup()
{
	Getter->Startup(LocalPlayer, FSimpleDelegate::CreateUObject(this, &ThisClass::OnDataSourcesReady));
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
	Setter->SetValue(LocalPlayer, StringValue);

	NotifySettingChanged(Reason);
}

double UPropertyScalarValueDynamic::GetValue() const
{
	const FString OutValue = Getter->GetValueAsString(LocalPlayer);

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
