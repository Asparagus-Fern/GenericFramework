// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Value/DiscreteValue_RotatorBox.h"

#include "MVVM/DiscreteValuesViewModel.h"
#include "MVVM/DiscreteValueViewModel.h"
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
	if (DiscreteValuesViewModel)
	{
		DiscreteValuesViewModel->SetValueByIndex(Value);
	}
}

void UDiscreteValue_RotatorBox::OnDiscreteValueAdded_Implementation(UDiscreteValueViewModel* Item)
{
	Super::OnDiscreteValueAdded_Implementation(Item);

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->AddTextLabel(Item->ValueDisplayName);
	}
}

void UDiscreteValue_RotatorBox::OnDiscreteValueRemoved_Implementation(UDiscreteValueViewModel* Item)
{
	Super::OnDiscreteValueRemoved_Implementation(Item);

	if (GenericRotator_PropertyValue)
	{
		GenericRotator_PropertyValue->RemoveTextLabel(Item->ValueDisplayName);
	}
}

void UDiscreteValue_RotatorBox::OnDiscreteValueChanged_Implementation()
{
	Super::OnDiscreteValueChanged_Implementation();

	if (GenericRotator_PropertyValue && DiscreteValuesViewModel)
	{
		GenericRotator_PropertyValue->SetSelectedItem(DiscreteValuesViewModel->CurrentValueIndex);
	}
}
