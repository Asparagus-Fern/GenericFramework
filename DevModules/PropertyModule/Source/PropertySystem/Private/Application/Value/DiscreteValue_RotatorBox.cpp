// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Application/Value/DiscreteValue_RotatorBox.h"

#include "MVVM/Data/Multi/MultiPropertyValueViewModel.h"
#include "UWidget/GenericRotatorBox.h"

void UDiscreteValue_RotatorBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->OnElementRotated.AddUniqueDynamic(this, &UDiscreteValue_RotatorBox::OnElementRotated);
	}
}

void UDiscreteValue_RotatorBox::NativeDestruct()
{
	Super::NativeDestruct();

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->OnElementRotated.RemoveAll(this);
	}
}

void UDiscreteValue_RotatorBox::OnElementRotated(int32 InIndex, const FText& InText)
{
	if (MultiPropertyValueViewModel)
	{
		MultiPropertyValueViewModel->SetSelectedValueByIndex(InIndex);
		MultiPropertyValueViewModel->NotifyPropertyChanged(EPropertyChangedReason::UserInput);
	}
}

void UDiscreteValue_RotatorBox::OnAllowWrapChanged_Implementation(bool IsAllowWrap)
{
	Super::OnAllowWrapChanged_Implementation(IsAllowWrap);

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->bAllowWrap = IsAllowWrap;
	}
}

void UDiscreteValue_RotatorBox::OnPropertyValueAdded_Implementation(const FString& InName, UPropertyViewModel* InViewModel)
{
	Super::OnPropertyValueAdded_Implementation(InName, InViewModel);

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->AddTextLabel(InViewModel->PropertyDisplayName);
	}
}

void UDiscreteValue_RotatorBox::OnPropertyValueRemoved_Implementation(const FString& InName, UPropertyViewModel* InViewModel)
{
	Super::OnPropertyValueRemoved_Implementation(InName, InViewModel);

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->RemoveTextLabel(InViewModel->PropertyDisplayName);
	}
}

void UDiscreteValue_RotatorBox::OnSelectedValueChanged_Implementation(const FString& SelectedValue)
{
	Super::OnSelectedValueChanged_Implementation(SelectedValue);

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->SetSelectedIndex(MultiPropertyValueViewModel->GetSelectedValueIndex());
	}
}
