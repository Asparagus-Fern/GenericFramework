// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"
// #include "PropertyScalarValueInterface.generated.h"

class FPropertyDataSource;

/**
 * 
 */
class PROPERTYPATHSYSTEM_API FPropertyScalarValueInterface
{
public:
	virtual ~FPropertyScalarValueInterface() = default;

	void SetDataSourceGetter(const TSharedRef<FPropertyDataSource>& InGetter);
	void SetDataSourceSetter(const TSharedRef<FPropertyDataSource>& InSetter);

	/* 获取属性值 */
	virtual double GetValue() const PURE_VIRTUAL(, return 0;);

	/* 设置属性值 */
	virtual void SetValue(double InValue, EPropertyChangeReason Reason = EPropertyChangeReason::Change) PURE_VIRTUAL(,);

	/* 获取标准化属性值 */
	virtual double GetValueNormalized() const;

	/* 设置标准化属性值 */
	virtual void SetValueNormalized(double InNormalizedValue);

	/* 获取默认值 */
	virtual TOptional<double> GetDefaultValue() const;

	/* 设置默认值 */
	virtual void SetDefaultValue(double InValue);

	/* 获取格式化的默认值 */
	TOptional<double> GetDefaultValueNormalized() const;

	/* 设置标准化默认值 */
	virtual void SetDefaultValueNormalized(double InNormalizedValue);

	/* 获取属性范围 */
	virtual TRange<double> GetSourceRange() const;

	/* 设置属性范围 */
	virtual void SetSourceRange(TRange<double> InRange);

	/* 获取属性步长 */
	virtual double GetSourceStep() const;

	/* 设置属性步长 */
	virtual void SetSourceStep(double InStep);

	/* 获取标准化步长 */
	virtual double GetSourceStepNormalized() const;

	/* 设置属性范围和步长 */
	virtual void SetSourceRangeAndStep(const TRange<double>& InRange, double InStep);

	/* 获取UI的最小限制 */
	virtual TOptional<double> GetMinimumLimit();

	/* 设置UI的最小限制 */
	virtual void SetMinimumLimit(const TOptional<double>& InMinimum);

	/* 获取UI的最大限制 */
	virtual TOptional<double> GetMaximumLimit();

	/* 设置UI的最大限制 */
	virtual void SetMaximumLimit(const TOptional<double>& InMaximum);

	/* 获取属性的显示文本格式 */
	virtual FText GetFormattedText() const PURE_VIRTUAL(, return FText::GetEmpty(););

protected:
	TSharedPtr<FPropertyDataSource> Getter;
	TSharedPtr<FPropertyDataSource> Setter;

	/* 属性默认值 */
	TOptional<double> DefaultValue;

	/* 属性初始值 */
	double InitialValue = 0;

	/* 属性的取值范围 */
	TRange<double> SourceRange = TRange<double>(0, 1);

	/* 属性的更改步长 */
	double SourceStep = 0.01;

	/* 属性UI可设置的最小值*/
	TOptional<double> Minimum;

	/* 属性UI可设置的最大值 */
	TOptional<double> Maximum;
};
