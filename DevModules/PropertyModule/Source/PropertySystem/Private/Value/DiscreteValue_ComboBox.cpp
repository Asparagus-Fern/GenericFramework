// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Value/DiscreteValue_ComboBox.h"

#include "Components/ComboBoxString.h"
#include "MVVM/DiscreteValuesViewModel.h"
#include "MVVM/DiscreteValueViewModel.h"

void UDiscreteValue_ComboBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (ComboBox_PropertyValue)
	{
		ComboBox_PropertyValue->OnSelectionChanged.AddUniqueDynamic(this, &UDiscreteValue_ComboBox::OnSelectionChanged);
	}
}

void UDiscreteValue_ComboBox::NativeDestruct()
{
	Super::NativeDestruct();

	if (ComboBox_PropertyValue)
	{
		ComboBox_PropertyValue->OnSelectionChanged.RemoveAll(this);
	}
}

void UDiscreteValue_ComboBox::OnSelectionChanged(FString SelectedItem, ESelectInfo::Type SelectionType)
{
	if (DiscreteValuesViewModel)
	{
		DiscreteValuesViewModel->SetValueByIndex(ComboBox_PropertyValue->FindOptionIndex(SelectedItem));
	}
}

void UDiscreteValue_ComboBox::OnDiscreteValueAdded_Implementation(UDiscreteValueViewModel* Item)
{
	Super::OnDiscreteValueAdded_Implementation(Item);

	if (ComboBox_PropertyValue)
	{
		ComboBox_PropertyValue->AddOption(Item->ValueDisplayName.ToString());
	}
}

void UDiscreteValue_ComboBox::OnDiscreteValueRemoved_Implementation(UDiscreteValueViewModel* Item)
{
	Super::OnDiscreteValueRemoved_Implementation(Item);

	if (ComboBox_PropertyValue)
	{
		ComboBox_PropertyValue->RemoveOption(Item->ValueDisplayName.ToString());
	}
}

void UDiscreteValue_ComboBox::OnDiscreteValueChanged_Implementation()
{
	Super::OnDiscreteValueChanged_Implementation();

	if (ComboBox_PropertyValue && DiscreteValuesViewModel)
	{
		ComboBox_PropertyValue->SetSelectedIndex(DiscreteValuesViewModel->CurrentValueIndex);
	}
}
