// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "MVVM/Data/Multi/BoolPropertyValueViewModel.h"

#include "StaticFunctions/StaticFunctions_Convert.h"

#define LOCTEXT_NAMESPACE "FPropertySystemModel"

static FString TrueStringValue = TEXT("true");
static FString FalseStringValue = TEXT("false");

UBoolPropertyValueViewModel::UBoolPropertyValueViewModel(const FObjectInitializer& FObjectInitializer)
	: Super(FObjectInitializer)
{
	bAllowWrap = true;

	UPropertyViewModel* FalseValue = CreateDefaultSubobject<UPropertyViewModel>(TEXT("False"));
	AddValue(FalseStringValue, FalseValue);

	UPropertyViewModel* TrueValue = CreateDefaultSubobject<UPropertyViewModel>(TEXT("True"));
	AddValue(TrueStringValue, TrueValue);
}

void UBoolPropertyValueViewModel::SetTrueText(const FText& InText)
{
	UPropertyViewModel* TrueProperty;
	if (FindViewModel(TrueStringValue, TrueProperty))
	{
		TrueProperty->SetPropertyDisplayName(InText);
	}
}

void UBoolPropertyValueViewModel::SetFalseText(const FText& InText)
{
	UPropertyViewModel* FalseProperty;
	if (FindViewModel(FalseStringValue, FalseProperty))
	{
		FalseProperty->SetPropertyDisplayName(InText);
	}
}

#undef LOCTEXT_NAMESPACE
