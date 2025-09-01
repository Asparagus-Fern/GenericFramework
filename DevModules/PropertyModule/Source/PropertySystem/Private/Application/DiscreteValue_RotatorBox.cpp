// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Application/DiscreteValue_RotatorBox.h"

#include "MVVM/Multi/MultiPropertyValueViewModel.h"
#include "MVVM/Single/SinglePropertyValueViewModel.h"
#include "UWidget/GenericRotatorBox.h"

void UDiscreteValue_RotatorBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->OnRotatedWithDirection.AddUniqueDynamic(this, &UDiscreteValue_RotatorBox::OnRotatedWithDirection);
	}
}

void UDiscreteValue_RotatorBox::NativeDestruct()
{
	Super::NativeDestruct();

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->OnRotatedWithDirection.RemoveAll(this);
	}
}

void UDiscreteValue_RotatorBox::OnRotatedWithDirection(int32 Value, ERotatorDirection RotatorDir)
{
	if (MultiPropertyValueViewModel)
	{
		MultiPropertyValueViewModel->SetSelectedValue(Value);
	}
}

void UDiscreteValue_RotatorBox::OnAllowWrapChanged_Implementation(bool IsAllowWrap)
{
	Super::OnAllowWrapChanged_Implementation(IsAllowWrap);

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->SetIsAllowWrap(MultiPropertyValueViewModel->bAllowWrap);
	}
}

void UDiscreteValue_RotatorBox::OnPropertyValueAdded_Implementation(USinglePropertyValueViewModel* ViewModel)
{
	Super::OnPropertyValueAdded_Implementation(ViewModel);

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->AddTextLabel(ViewModel->PropertyValueDisplayName);
	}
}

void UDiscreteValue_RotatorBox::OnPropertyValueRemoved_Implementation(USinglePropertyValueViewModel* ViewModel)
{
	Super::OnPropertyValueRemoved_Implementation(ViewModel);

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->RemoveTextLabel(ViewModel->PropertyValueDisplayName);
	}
}

void UDiscreteValue_RotatorBox::OnSelectedValueIndexChanged_Implementation(int32 SelectedValueIndex)
{
	Super::OnSelectedValueIndexChanged_Implementation(SelectedValueIndex);

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->SetSelectedItem(SelectedValueIndex);
	}
}
