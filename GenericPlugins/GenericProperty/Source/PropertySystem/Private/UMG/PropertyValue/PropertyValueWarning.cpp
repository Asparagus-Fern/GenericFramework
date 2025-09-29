// Copyright ChenTaiye 2025. All Rights Reserved.


#include "UMG/PropertyValue/PropertyValueWarning.h"

#include "Components/TextBlock.h"

const FText& UPropertyValueWarning::GetWarningText() const
{
	return WarningText;
}

void UPropertyValueWarning::SetWarningText(const FText& InText)
{
	WarningText = InText;
	OnWarningTextChanged(WarningText);
}

void UPropertyValueWarning::OnWarningTextChanged_Implementation(const FText& InText)
{
}
