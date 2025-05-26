// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/Discrete/PropertyDiscreteValue_Text.h"

FText UPropertyDiscreteValue_Text::GetTextValue() const
{
	return FText::FromString(GetValueAsString());
}

void UPropertyDiscreteValue_Text::SetTextValue(const FText& InValue)
{
	SetValueFromString(InValue.ToString());
}

FText UPropertyDiscreteValue_Text::GetDefaultTextValue() const
{
	return FText::FromString(GetDefaultValueAsString());
}

void UPropertyDiscreteValue_Text::SetDefaultTextValue(const FText& InValue)
{
	SetDefaultValueFromString(InValue.ToString());
}
