// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/PropertyDiscreteValue_Rotator.h"

FRotator UPropertyDiscreteValue_Rotator::GetDefaultRotatorValue() const
{
	FRotator ValueRotator;
	ValueRotator.InitFromString(GetDefaultValue());
	return ValueRotator;
}

void UPropertyDiscreteValue_Rotator::SetDefaultRotatorValue(const FRotator& InValue)
{
	SetDefaultValue(InValue.ToString());
}

FRotator UPropertyDiscreteValue_Rotator::GetRotatorValue() const
{
		StaticStruct<>()->
	
	FRotator ValueRotator;
	ValueRotator.InitFromString(GetValue());
	return ValueRotator;
}

void UPropertyDiscreteValue_Rotator::SetRotatorValue(const FRotator& InValue)
{
	SetValue(InValue.ToString());
}

void UPropertyDiscreteValue_Rotator::AddRotatorOption(FName InOptionName, FRotator InOptionValue, const FText& InOptionText)
{
	AddOption(InOptionName, InOptionValue.ToString(), InOptionText);
}
