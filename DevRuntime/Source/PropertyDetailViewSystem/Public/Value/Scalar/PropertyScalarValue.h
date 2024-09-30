// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PropertyType.h"
#include "Value/PropertyValueBase.h"
#include "PropertyScalarValue.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROPERTYDETAILVIEWSYSTEM_API UPropertyScalarValue : public UPropertyValueBase
{
	GENERATED_BODY()

public:
	virtual void OnInitialized() override;
	
	void SetValueNormalized(double NormalizedValue);
	double GetValueNormalized() const;

	virtual TOptional<double> GetDefaultValue() const PURE_VIRTUAL(, return TOptional<double>(););
	virtual void SetValue(double Value, EPropertyChangeReason Reason = EPropertyChangeReason::Change) PURE_VIRTUAL(,);
	virtual double GetValue() const PURE_VIRTUAL(, return 0;);
	virtual TRange<double> GetSourceRange() const PURE_VIRTUAL(, return TRange<double>(););
	virtual double GetSourceStep() const PURE_VIRTUAL(, return 0.01;);
	virtual FText GetFormattedText() const PURE_VIRTUAL(, return FText::GetEmpty(););

	TOptional<double> GetDefaultValueNormalized() const;
	double GetNormalizedStepSize() const;
};
