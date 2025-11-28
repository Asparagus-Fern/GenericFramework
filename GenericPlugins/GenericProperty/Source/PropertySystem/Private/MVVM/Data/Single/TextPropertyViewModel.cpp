// Copyright ChenTaiye 2025. All Rights Reserved.


#include "MVVM/Data/Single/TextPropertyViewModel.h"

FString UTextPropertyViewModel::GetInitialValueAsString()
{
	return InitialValue.ToString();
}

void UTextPropertyViewModel::SetInitialValueFromString(const FString& InValue)
{
	InitialValue = FText::FromString(InValue);
}

FString UTextPropertyViewModel::GetCurrentValueAsString()
{
	return CurrentValue.ToString();
}

void UTextPropertyViewModel::SetCurrentValueFromString(const FString& InValue)
{
	CurrentValue = FText::FromString(InValue);
}
