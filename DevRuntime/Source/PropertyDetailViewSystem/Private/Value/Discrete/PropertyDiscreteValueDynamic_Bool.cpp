// Fill out your copyright notice in the Description page of Project Settings.


#include "Value/Discrete/PropertyDiscreteValueDynamic_Bool.h"

#define LOCTEXT_NAMESPACE "GameSettingValueDiscreteDynamic_Bool"

UPropertyDiscreteValueDynamic_Bool::UPropertyDiscreteValueDynamic_Bool()
{
	AddOption(TEXT("false"), LOCTEXT("OFF", "OFF"));
	AddOption(TEXT("true"), LOCTEXT("ON", "ON"));
}

void UPropertyDiscreteValueDynamic_Bool::SetDefaultValue(bool Value)
{
	DefaultValue = LexToString(Value);
}

void UPropertyDiscreteValueDynamic_Bool::SetTrueText(const FText& InText)
{
	RemoveOption(TEXT("true"));
	AddOption(TEXT("true"), InText);
}

void UPropertyDiscreteValueDynamic_Bool::SetFalseText(const FText& InText)
{
	RemoveOption(TEXT("false"));
	AddOption(TEXT("false"), InText);
}

#undef LOCTEXT_NAMESPACE
