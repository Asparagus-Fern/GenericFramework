// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Application/PropertyDiscreteValue_String.h"

FString UPropertyDiscreteValue_String::GetDefaultStringValue() const
{
	return GetDefaultValue();
}

void UPropertyDiscreteValue_String::SetDefaultStringValue(FString InValue)
{
	SetDefaultValue(InValue);
}

FString UPropertyDiscreteValue_String::GetStringValue() const
{
	return GetValue();
}

void UPropertyDiscreteValue_String::SetStringValue(FString InValue)
{
	SetValue(InValue);
}

void UPropertyDiscreteValue_String::AddStringOption(FName InOptionName, FString InOptionValue, const FText& InOptionText)
{
	AddOption(InOptionName, InOptionValue, InOptionText);
}
