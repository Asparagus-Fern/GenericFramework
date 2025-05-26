// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/Discrete/PropertyDiscreteValue_String.h"

FString UPropertyDiscreteValue_String::GetStringValue() const
{
	return GetValueAsString();
}

void UPropertyDiscreteValue_String::SetStringValue(const FString& InValue)
{
	SetValueFromString(InValue);
}

FString UPropertyDiscreteValue_String::GetDefaultStringValue() const
{
	return GetDefaultValueAsString();
}

void UPropertyDiscreteValue_String::SetDefaultStringValue(const FString& InValue)
{
	SetDefaultValueFromString(InValue);
}
