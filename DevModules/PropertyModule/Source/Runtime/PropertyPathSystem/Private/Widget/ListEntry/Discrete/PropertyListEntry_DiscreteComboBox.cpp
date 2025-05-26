// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Widget/ListEntry/Discrete/PropertyListEntry_DiscreteComboBox.h"

#include "Base/PropertyEditCondition.h"
#include "Components/ComboBoxString.h"
#include "Value/Discrete/PropertyDiscreteValue.h"

void UPropertyListEntry_DiscreteComboBox::SetPropertyEntity(UPropertyEntity* InProperty)
{
	Super::SetPropertyEntity(InProperty);
	
	Refresh();
}

void UPropertyListEntry_DiscreteComboBox::RefreshEditableState(FPropertyEditableState InEditableState)
{
	Super::RefreshEditableState(InEditableState);

	const bool bLocalIsEnabled = InEditableState.IsEnabled();
	ComboBox_PropertyValue->SetIsEnabled(bLocalIsEnabled);
}

void UPropertyListEntry_DiscreteComboBox::Refresh()
{
	ComboBox_PropertyValue->ClearOptions();
	for (auto& Option : DiscreteProperty->GetAllOptionText())
	{
		ComboBox_PropertyValue->AddOption(Option.ToString());
	}

	ComboBox_PropertyValue->SetSelectedIndex(DiscreteProperty->GetDiscreteOptionIndex());
}
