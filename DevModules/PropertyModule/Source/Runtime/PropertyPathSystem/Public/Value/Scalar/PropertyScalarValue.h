// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyScalarValueInterface.h"
#include "PropertyType.h"
#include "Value/PropertyValueBase.h"
#include "PropertyScalarValue.generated.h"

class FPropertyDataSource;
typedef TFunction<FText(double SourceValue, double NormalizedValue)> FPropertyScalarFormatFunction;

/**
 * 
 */
struct PROPERTYPATHSYSTEM_API FPropertyScalarFormat
{
public:
	/* 以小数格式显示 */
	static FPropertyScalarFormatFunction FormatAsDigits(int32 IntegralDigits, int32 FractionalDigit);

	/* 以百分数格式显示 */
	static FPropertyScalarFormatFunction FormatAsPercent(int32 FractionalDigit);

private:
	static FNumberFormattingOptions* GetNumberFormattingOptions(int32 IntegralDigits, int32 FractionalDigits);
};

/**
 * 连续类型属性基类
 */
UCLASS()
class PROPERTYPATHSYSTEM_API UPropertyScalarValue : public UPropertyValueBase, public FPropertyScalarValueInterface
{
	GENERATED_BODY()

	/* UPropertyEntity */
public:
	virtual void OnInitialized() override;
	virtual void Startup() override;

protected:
	void OnDataSourcesReady();

	/* UPropertyValueBase */
public:
	virtual void StoreInitial() override;
	virtual void ResetToInitial() override;
	virtual void ResetToDefault() override;

	/** FPropertyScalarValueInterface */
public:
	virtual double GetValue() const override;
	virtual void SetValue(double InValue, EPropertyChangeReason Reason = EPropertyChangeReason::Change) override;

	virtual FText GetFormattedText() const override;

	/* UPropertyScalarValue */
public:
	/* 获取显示格式 */
	FPropertyScalarFormatFunction GetDisplayFormat();
	
	/* 设置显示格式 */
	void SetDisplayFormat(const FPropertyScalarFormatFunction& InDisplayFormat);

protected:
	FPropertyScalarFormatFunction DisplayFormat;
};
