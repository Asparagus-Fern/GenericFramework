// Copyright ChenTaiye 2025. All Rights Reserved.


#include "MVVM/Single/SinglePropertyValueViewModel.h"

void USinglePropertyValueViewModel::InitializeWithProperty(FName InPropertyName, const FProperty* InProperty)
{
	check(InProperty);

	PropertyValueName = InPropertyName;
	PropertyValueDisplayName = InProperty->GetDisplayNameText();
	PropertyValueTooltip = InProperty->GetToolTipText();
}
