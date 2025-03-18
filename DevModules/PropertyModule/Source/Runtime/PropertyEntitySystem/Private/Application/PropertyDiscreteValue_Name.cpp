// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/PropertyDiscreteValue_Name.h"

FName UPropertyDiscreteValue_Name::GetDefaultNameValue() const
{
	return FName(GetDefaultValue());
}

void UPropertyDiscreteValue_Name::SetDefaultNameValue(FName InValue)
{
	SetDefaultValue(InValue.ToString());
}

FName UPropertyDiscreteValue_Name::GetNameValue() const
{
	return FName(GetValue());
}

void UPropertyDiscreteValue_Name::SetNameValue(FName InValue)
{
	SetValue(InValue.ToString());
}

void UPropertyDiscreteValue_Name::AddNameOption(FName InOptionName, FName InOptionValue, const FText& InOptionText)
{
	AddOption(InOptionName, InOptionValue.ToString(), InOptionText);
}
