// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Application/Value/DiscreteValue_ComboBox.h"

#include "Components/ComboBoxString.h"
#include "MVVM/Data/Multi/MultiPropertyValueViewModel.h"

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
	MultiPropertyValueViewModel->SetSelectedValue(SelectedItem);
	MultiPropertyValueViewModel->NotifyPropertyChanged(EPropertyChangedReason::UserInput);
}

void UDiscreteValue_ComboBox::OnPropertyValueAdded_Implementation(const FString& InName, UPropertyViewModel* InViewModel)
{
	Super::OnPropertyValueAdded_Implementation(InName, InViewModel);

	if (ComboBox_PropertyValue)
	{
		ComboBox_PropertyValue->AddOption(InName);
	}
}

void UDiscreteValue_ComboBox::OnPropertyValueRemoved_Implementation(const FString& InName, UPropertyViewModel* InViewModel)
{
	Super::OnPropertyValueRemoved_Implementation(InName, InViewModel);

	if (ComboBox_PropertyValue)
	{
		ComboBox_PropertyValue->RemoveOption(InName);
	}
}

void UDiscreteValue_ComboBox::OnSelectedValueChanged_Implementation(const FString& SelectedValue)
{
	Super::OnSelectedValueChanged_Implementation(SelectedValue);

	if (ComboBox_PropertyValue)
	{
		ComboBox_PropertyValue->SetSelectedOption(SelectedValue);
	}
}
