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
UCLASS(MinimalAPI)
class UPropertyScalarValue : public UPropertyValueBase, public FPropertyScalarValueInterface
{
	GENERATED_BODY()

	/* UPropertyEntity */
public:
	PROPERTYPATHSYSTEM_API virtual void OnInitialized() override;
	PROPERTYPATHSYSTEM_API virtual void Startup() override;

protected:
	void OnDataSourcesReady();

	/* UPropertyValueBase */
public:
	PROPERTYPATHSYSTEM_API virtual void StoreInitial() override;
	PROPERTYPATHSYSTEM_API virtual void ResetToInitial() override;
	PROPERTYPATHSYSTEM_API virtual void ResetToDefault() override;

	/* FPropertyScalarValueInterface */
public:
	PROPERTYPATHSYSTEM_API virtual double GetValue() const override;
	PROPERTYPATHSYSTEM_API virtual void SetValue(double InValue, EPropertyChangeReason Reason = EPropertyChangeReason::Change) override;

	PROPERTYPATHSYSTEM_API virtual FText GetFormattedText() const override;

	/* UPropertyScalarValue */
public:
	/* 获取显示格式 */
	PROPERTYPATHSYSTEM_API FPropertyScalarFormatFunction GetDisplayFormat();

	/* 设置显示格式 */
	PROPERTYPATHSYSTEM_API void SetDisplayFormat(const FPropertyScalarFormatFunction& InDisplayFormat);

protected:
	FPropertyScalarFormatFunction DisplayFormat;
};
