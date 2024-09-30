// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyScalarValue.h"
#include "PropertyScalarValueDynamic.generated.h"

class FPropertyDataSource;
typedef TFunction<FText(double SourceValue, double NormalizedValue)> FSettingScalarFormatFunction;

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyScalarValueDynamic : public UPropertyScalarValue
{
	GENERATED_BODY()

public:
	static FSettingScalarFormatFunction FormatAsInteger;
	static FSettingScalarFormatFunction FormatAsOneFractionalDigit;
	static FSettingScalarFormatFunction FormatAsTwoFractionalDigits;
	static FSettingScalarFormatFunction FormatAsThreeFractionalDigits;
	static FSettingScalarFormatFunction FormatAsPercent;
	static FSettingScalarFormatFunction FormatAsPercent_OneFractionalDigit;

private:
	static FNumberFormattingOptions* GetNumberFormattingOptions(int32 IntegralDigits, int32 FractionalDigits);

	/* UPropertyEntity */
public:
	virtual void Startup() override;

protected:
	void OnDataSourcesReady();

	/* UPropertyValueBase */
public:
	virtual void StoreInitial() override;
	virtual void ResetToDefault() override;
	virtual void RestoreToInitial() override;

	/** UGameSettingValueScalar */
public:
	virtual TOptional<double> GetDefaultValue() const override;
	virtual void SetValue(double InValue, EPropertyChangeReason Reason = EPropertyChangeReason::Change) override;
	virtual double GetValue() const override;
	virtual TRange<double> GetSourceRange() const override;
	virtual double GetSourceStep() const override;
	virtual FText GetFormattedText() const override;

	/* UPropertyScalarValueDynamic */
public:
	void SetDataSourceGetter(const TSharedRef<FPropertyDataSource>& InGetter);
	void SetDataSourceSetter(const TSharedRef<FPropertyDataSource>& InSetter);

	void SetMinimumLimit(const TOptional<double>& InMinimum);
	void SetMaximumLimit(const TOptional<double>& InMaximum);

	void SetSourceRangeAndStep(const TRange<double>& InRange, double InSourceStep);
	void SetDisplayFormat(FSettingScalarFormatFunction InDisplayFormat);

protected:
	TSharedPtr<FPropertyDataSource> Getter;
	TSharedPtr<FPropertyDataSource> Setter;

	TOptional<double> DefaultValue;
	double InitialValue = 0;

	TRange<double> SourceRange = TRange<double>(0, 1);
	double SourceStep = 0.01;
	TOptional<double> Minimum;
	TOptional<double> Maximum;

	FSettingScalarFormatFunction DisplayFormat;
};
