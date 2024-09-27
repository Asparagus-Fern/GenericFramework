// Fill out your copyright notice in the Description page of Project Settings.


#include "Value/Discrete/PropertyDiscreteValueDynamic_Color.h"

void UPropertyDiscreteValueDynamic_Color::SetDefaultValue(FLinearColor InColor)
{
	SetDefaultValueFromString(InColor.ToString());
}

void UPropertyDiscreteValueDynamic_Color::AddColorOption(FLinearColor InColor)
{
	const FColor SRGBColor = InColor.ToFColor(true);
	AddOption(InColor.ToString(), FText::FromString(FString::Printf(TEXT("#%02X%02X%02X"), SRGBColor.R, SRGBColor.G, SRGBColor.B)));
}

void UPropertyDiscreteValueDynamic_Color::RemoveColorOption(FLinearColor InColor)
{
	RemoveOption(InColor.ToString());
}

FLinearColor UPropertyDiscreteValueDynamic_Color::GetValue() const
{
	const FString Value = GetValueAsString();

	FLinearColor ColorValue;
	bool bSuccess = ColorValue.InitFromString(Value);
	ensure(bSuccess);

	return ColorValue;
}

void UPropertyDiscreteValueDynamic_Color::SetValue(FLinearColor InColor)
{
	SetValueFromString(InColor.ToString());
}
