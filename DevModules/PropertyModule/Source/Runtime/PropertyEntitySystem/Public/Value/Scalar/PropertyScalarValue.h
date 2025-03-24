// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Value/PropertyValueEntity.h"
#include "PropertyScalarValue.generated.h"

class FPropertyDataSource;
typedef TFunction<FText(double SourceValue, double NormalizedValue)> FPropertyScalarFormatFunction;

/**
 * 
 */
struct FPropertyScalarFormat
{
public:
	static FPropertyScalarFormatFunction FormatAsDigits(int32 IntegralDigits, int32 FractionalDigit);
	static FPropertyScalarFormatFunction FormatAsPercent(int32 FractionalDigit);

private:
	static FNumberFormattingOptions* GetNumberFormattingOptions(int32 IntegralDigits, int32 FractionalDigits);
};

/**
 * 
 */
UCLASS()
class PROPERTYENTITYSYSTEM_API UPropertyScalarValue : public UPropertyValueEntity
{
	GENERATED_BODY()

	/* UPropertyEntity */
protected:
	virtual void Startup() override;
	virtual void OnInitialized() override;

	/* UPropertyValueEntity */
public:
	virtual void ResetToDefault() override;
	virtual void StoreToInitial() override;
	virtual void ResetToInitial() override;

	/* UPropertyScalarValue */
protected:
	void OnDataSourcesReady();

public:
	void SetDataSourceGetter(const TSharedRef<FPropertyDataSource>& InGetter);
	void SetDataSourceSetter(const TSharedRef<FPropertyDataSource>& InSetter);

	double GetDefaultValue() const;
	double GetDefaultValueNormalized() const;
	void SetDefaultValue(double InValue);

	double GetValue() const;
	void SetValue(double InValue, EPropertyChangeReason Reason = EPropertyChangeReason::Change);

	double GetValueNormalized() const;
	void SetValueNormalized(double NormalizedValue);

	void SetValueRangeAndStep(const TRange<double>& InRange, double InStep);

	TRange<double> GetValueRange() const;
	void SetValueRange(const TRange<double>& InRange);

	double GetValueStep() const;
	double GetValueStepNormalized() const;
	void SetValueStep(double InStep);

	FText GetFormattedText() const;
	void SetFormattedText(FPropertyScalarFormatFunction InDisplayFormat);

protected:
	TSharedPtr<FPropertyDataSource> Getter;
	TSharedPtr<FPropertyDataSource> Setter;

	double DefaultValue = 0;
	double InitialValue = 0;

	TRange<double> ValueRange = TRange<double>(0, 1);
	double ValueStep = 0.001;

	TOptional<double> MinimumUIValue;
	TOptional<double> MaximumUIValue;

	FPropertyScalarFormatFunction DisplayFormat;
};
