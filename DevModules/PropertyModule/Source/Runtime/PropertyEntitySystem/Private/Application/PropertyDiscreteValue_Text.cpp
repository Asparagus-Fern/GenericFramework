// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Application/PropertyDiscreteValue_Text.h"

FText UPropertyDiscreteValue_Text::GetDefaultTextValue() const
{
	return FText::FromString(GetDefaultValue());
}

void UPropertyDiscreteValue_Text::SetDefaultTextValue(FText InValue)
{
	SetDefaultValue(InValue.ToString());
}

FText UPropertyDiscreteValue_Text::GetTextValue() const
{
	return FText::FromString(GetValue());
}

void UPropertyDiscreteValue_Text::SetTextValue(FText InValue)
{
	SetValue(InValue.ToString());
}

void UPropertyDiscreteValue_Text::AddTextOption(FName InOptionName, FText InOptionValue, const FText& InOptionText)
{
	AddOption(InOptionName, InOptionValue.ToString(), InOptionText);
}
