// Copyright ChenTaiye 2025. All Rights Reserved.

#include "MVVM/DiscreteValueViewModel.h"

void UDiscreteValueViewModel::InitializeWithProperty(const FProperty* InProperty)
{
	check(InProperty);

	ValueName = InProperty->GetFName();
	ValueDisplayName = InProperty->GetDisplayNameText();
	ValueTooltip = InProperty->GetToolTipText();
}