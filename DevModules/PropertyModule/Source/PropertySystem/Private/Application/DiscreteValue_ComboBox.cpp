// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Application/DiscreteValue_ComboBox.h"

#include "Components/ComboBoxString.h"
#include "MVVM/Multi/MultiPropertyValueViewModel.h"
#include "MVVM/Single/SinglePropertyValueViewModel.h"

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
	MultiPropertyValueViewModel->SetSelectedValue(ComboBox_PropertyValue->FindOptionIndex(SelectedItem));
}

void UDiscreteValue_ComboBox::OnPropertyValueAdded_Implementation(USinglePropertyValueViewModel* ViewModel)
{
	Super::OnPropertyValueAdded_Implementation(ViewModel);

	if (ComboBox_PropertyValue)
	{
		ComboBox_PropertyValue->AddOption(ViewModel->PropertyValueDisplayName.ToString());
	}
}

void UDiscreteValue_ComboBox::OnPropertyValueRemoved_Implementation(USinglePropertyValueViewModel* ViewModel)
{
	Super::OnPropertyValueRemoved_Implementation(ViewModel);

	if (ComboBox_PropertyValue)
	{
		ComboBox_PropertyValue->RemoveOption(ViewModel->PropertyValueDisplayName.ToString());
	}
}

void UDiscreteValue_ComboBox::OnSelectedValueIndexChanged_Implementation(USinglePropertyValueViewModel* ViewModel)
{
	Super::OnSelectedValueIndexChanged_Implementation(ViewModel);

	if (ComboBox_PropertyValue)
	{
		ComboBox_PropertyValue->SetSelectedIndex(MultiPropertyValueViewModel->SelectedValueIndex);
	}
}
