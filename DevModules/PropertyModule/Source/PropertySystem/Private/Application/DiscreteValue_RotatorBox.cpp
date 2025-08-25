// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Application/DiscreteValue_RotatorBox.h"

#include "PropertyType.h"
#include "MVVM/Multi/MultiPropertyValueViewModel.h"
#include "MVVM/Single/SinglePropertyValueViewModel.h"
#include "UWidget/GenericRotatorBox.h"

void UDiscreteValue_RotatorBox::NativeConstruct()
{
	Super::NativeConstruct();

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->OnRotatedWithDirection.AddUniqueDynamic(this, &UDiscreteValue_RotatorBox::OnRotatedWithDirection);

		GenericRotator_PropertyValue->SetIsAllowWrap(MultiPropertyValueViewModel->bAllowWrap);
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

void UDiscreteValue_RotatorBox::NativeOnViewModelInitialized()
{
	Super::NativeOnViewModelInitialized();

	if (MultiPropertyValueViewModel)
	{
		MVVM_REGISTRY(OnAllowWrapChangedHandle, MultiPropertyValueViewModel, bAllowWrap, HandleOnAllowWrapChanged)
	}
}

void UDiscreteValue_RotatorBox::NativeOnViewModelDeinitialized()
{
	Super::NativeOnViewModelDeinitialized();

	if (MultiPropertyValueViewModel)
	{
		MVVM_UNREGISTRY(OnAllowWrapChangedHandle, MultiPropertyValueViewModel, bAllowWrap)
	}
}

void UDiscreteValue_RotatorBox::OnRotatedWithDirection(int32 Value, ERotatorDirection RotatorDir)
{
	MultiPropertyValueViewModel->SetSelectedValue(Value);
}

void UDiscreteValue_RotatorBox::HandleOnAllowWrapChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	GenericRotator_PropertyValue->SetIsAllowWrap(MultiPropertyValueViewModel->bAllowWrap);
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

void UDiscreteValue_RotatorBox::OnSelectedValueIndexChanged_Implementation(USinglePropertyValueViewModel* ViewModel)
{
	Super::OnSelectedValueIndexChanged_Implementation(ViewModel);

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->SetSelectedItem(MultiPropertyValueViewModel->SelectedValueIndex);
	}
}
