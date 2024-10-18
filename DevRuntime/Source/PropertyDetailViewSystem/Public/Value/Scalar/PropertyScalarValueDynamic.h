// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyScalarValue.h"
#include "PropertyScalarValueDynamic.generated.h"

class FPropertyDataSource;
typedef TFunction<FText(double SourceValue, double NormalizedValue)> FPropertyScalarFormatFunction;

/**
 * 
 */
UCLASS()
class PROPERTYDETAILVIEWSYSTEM_API UPropertyScalarValueDynamic : public UPropertyScalarValue
{
	GENERATED_BODY()

public:
	/* 以小数格式显示 */
	static FPropertyScalarFormatFunction FormatAsDigits(int32 IntegralDigits, int32 FractionalDigit);

	/* 以百分数格式显示 */
	static FPropertyScalarFormatFunction FormatAsPercent(int32 FractionalDigit);

private:
	static FNumberFormattingOptions* GetNumberFormattingOptions(int32 IntegralDigits, int32 FractionalDigits);

	/* UPropertyEntity */
public:
	virtual void OnInitialized() override;
	virtual void Startup() override;

protected:
	void OnDataSourcesReady();

	/* UPropertyValueBase */
public:
	virtual void StoreInitial() override;
	virtual void ResetToDefault() override;
	virtual void RestoreToInitial() override;

	/** UPropertyScalarValue */
public:
	virtual TOptional<double> GetDefaultValue() const override;
	virtual void SetDefaultValue(double InValue) override;

	virtual double GetValue() const override;
	virtual void SetValue(double InValue, EPropertyChangeReason Reason = EPropertyChangeReason::Change) override;

	virtual TRange<double> GetSourceRange() const override;
	virtual double GetSourceStep() const override;
	virtual FText GetFormattedText() const override;

	/* UPropertyScalarValueDynamic */
public:
	void SetDataSourceGetter(const TSharedRef<FPropertyDataSource>& InGetter);
	void SetDataSourceSetter(const TSharedRef<FPropertyDataSource>& InSetter);

	/* 设置UI的最小限制 */
	void SetMinimumLimit(const TOptional<double>& InMinimum);

	/* 设置UI的最大限制 */
	void SetMaximumLimit(const TOptional<double>& InMaximum);

	void SetSourceRangeAndStep(const TRange<double>& InRange, double InSourceStep);
	void SetSourceRange(const TRange<double>& InRange);
	void SetSourceStep(double InSourceStep);

	/* 设置显示格式 */
	void SetDisplayFormat(FPropertyScalarFormatFunction InDisplayFormat);

protected:
	TSharedPtr<FPropertyDataSource> Getter;
	TSharedPtr<FPropertyDataSource> Setter;

	TOptional<double> DefaultValue;
	double InitialValue = 0;

	/* 属性的取值范围 */
	TRange<double> SourceRange = TRange<double>(0, 1);

	/* 属性的更改步长 */
	double SourceStep = 0.01;

	/* 属性UI可设置的最小值*/
	TOptional<double> Minimum;

	/* 属性UI可设置的最大值 */
	TOptional<double> Maximum;

	FPropertyScalarFormatFunction DisplayFormat;
};
