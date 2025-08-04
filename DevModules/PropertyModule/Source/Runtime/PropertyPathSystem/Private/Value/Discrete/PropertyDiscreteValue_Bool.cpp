// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/Discrete/PropertyDiscreteValue_Bool.h"

#define LOCTEXT_NAMESPACE "FPropertyPathSystemModule"

UPropertyDiscreteValue_Bool::UPropertyDiscreteValue_Bool()
{
	AddOption(TEXT("false"), LOCTEXT("OFF", "False"));
	AddOption(TEXT("true"), LOCTEXT("ON", "True"));
}

bool UPropertyDiscreteValue_Bool::GetDefaultBoolValue() const
{
	const FString ValueString = GetDefaultValueAsString();

	bool BoolValue;
	LexFromString(BoolValue, *ValueString);

	return BoolValue;
}

void UPropertyDiscreteValue_Bool::SetDefaultBoolValue(bool InValue)
{
	SetDefaultValueFromString(LexToString(InValue));
}

void UPropertyDiscreteValue_Bool::SetTrueText(const FText& InText)
{
	RemoveOption(TEXT("true"));
	AddOption(TEXT("true"), InText);
}

void UPropertyDiscreteValue_Bool::SetFalseText(const FText& InText)
{
	RemoveOption(TEXT("false"));
	AddOption(TEXT("false"), InText);
}

#undef LOCTEXT_NAMESPACE
