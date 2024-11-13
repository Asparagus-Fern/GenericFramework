// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"
#include "Value/PropertyValueBase.h"
#include "PropertyScalarValue.generated.h"

/**
 * 连续类型属性基类
 */
UCLASS(Abstract)
class PROPERTYDETAILVIEWSYSTEM_API UPropertyScalarValue : public UPropertyValueBase
{
	GENERATED_BODY()

public:
	virtual void OnInitialized() override;

	/* 设置属性值，将格式化成0~1 */
	void SetValueNormalized(double NormalizedValue);

	/* 获取格式化成0~1的属性值 */
	double GetValueNormalized() const;

	/* 获取默认值 */
	virtual TOptional<double> GetDefaultValue() const PURE_VIRTUAL(, return TOptional<double>(););

	/* 设置默认值 */
	virtual void SetDefaultValue(double Value) PURE_VIRTUAL(,);

	/* 获取属性值 */
	virtual double GetValue() const PURE_VIRTUAL(, return 0;);

	/* 设置属性值 */
	virtual void SetValue(double Value, EPropertyChangeReason Reason = EPropertyChangeReason::Change) PURE_VIRTUAL(,);

	/* 获取属性范围 */
	virtual TRange<double> GetSourceRange() const PURE_VIRTUAL(, return TRange<double>(););

	/* 获取属性步长 */
	virtual double GetSourceStep() const PURE_VIRTUAL(, return 0.01;);

	/* 获取属性的显示文本格式 */
	virtual FText GetFormattedText() const PURE_VIRTUAL(, return FText::GetEmpty(););

	/* 获取格式化的默认值 */
	TOptional<double> GetDefaultValueNormalized() const;

	/* 获取格式化的步长 */
	double GetNormalizedStepSize() const;
};
