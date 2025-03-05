// Fill out your copyright notice in the Description page of Project Settings.


#include "Application/PropertyDiscreteValue_Bool.h"

static FName TrueOptionName = FName("True");
static FName FalseOptionName = FName("False");

#define LOCTEXT_NAMESPACE "UPropertyDiscreteValue_Bool"

UPropertyDiscreteValue_Bool::UPropertyDiscreteValue_Bool()
{
	UPropertyDiscreteOption* TrueOption = CreateDefaultSubobject<UPropertyDiscreteOption>("True");
	TrueOption->SetPropertyName(TrueOptionName);
	TrueOption->SetDisplayName(LOCTEXT("TrueOption", "On"));
	TrueOption->SetOptionValue(TEXT("true"));

	UPropertyDiscreteOption* FalseOption = CreateDefaultSubobject<UPropertyDiscreteOption>("False");
	FalseOption->SetPropertyName(FalseOptionName);
	FalseOption->SetDisplayName(LOCTEXT("FalseOption", "Off"));
	FalseOption->SetOptionValue(TEXT("false"));

	Options.Add(TrueOption);
	Options.Add(FalseOption);
}

void UPropertyDiscreteValue_Bool::SetDefaultValue(bool InValue)
{
	DefaultValue = LexToString(InValue);
}

void UPropertyDiscreteValue_Bool::SetTrueText(const FText& InText)
{
	GetOption(TrueOptionName)->SetDisplayName(InText);
}

void UPropertyDiscreteValue_Bool::SetFalseText(const FText& InText)
{
	GetOption(FalseOptionName)->SetDisplayName(InText);
}

void UPropertyDiscreteValue_Bool::SetTrueDescriptionText(const FText& InText)
{
	GetOption(TrueOptionName)->SetDescriptionText(InText);
}

void UPropertyDiscreteValue_Bool::SetFalseDescriptionText(const FText& InText)
{
	GetOption(FalseOptionName)->SetDescriptionText(InText);
}

#undef LOCTEXT_NAMESPACE
