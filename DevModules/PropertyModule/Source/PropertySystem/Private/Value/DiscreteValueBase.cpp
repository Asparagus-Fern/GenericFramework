// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Value/DiscreteValueBase.h"

#include "MVVM/DiscreteValuesViewModel.h"

void UDiscreteValueBase::NativeConstruct()
{
	Super::NativeConstruct();

	if (DiscreteValuesViewModel)
	{
		DiscreteValuesViewModel->OnDiscreteValueAddedEvent.AddUniqueDynamic(this, &UDiscreteValueBase::HandleOnDiscreteValueAdded);
		DiscreteValuesViewModel->OnDiscreteValueRemovedEvent.AddUniqueDynamic(this, &UDiscreteValueBase::HandleOnDiscreteValueRemoved);
		OnCurrentValueIndexChangedHandle = DiscreteValuesViewModel->AddFieldValueChangedDelegate(UDiscreteValuesViewModel::FFieldNotificationClassDescriptor::CurrentValueIndex, UDiscreteValuesViewModel::FFieldValueChangedDelegate::CreateUObject(this, &UDiscreteValueBase::OnCurrentValueIndexChanged));

		for (auto& Value : DiscreteValuesViewModel->Values)
		{
			HandleOnDiscreteValueAdded(Value);
		}
	}

	OnDiscreteValueChanged();
}

void UDiscreteValueBase::NativeDestruct()
{
	Super::NativeDestruct();

	DiscreteValuesViewModel->OnDiscreteValueAddedEvent.RemoveAll(this);
	DiscreteValuesViewModel->OnDiscreteValueRemovedEvent.RemoveAll(this);
	DiscreteValuesViewModel->RemoveFieldValueChangedDelegate(UDiscreteValuesViewModel::FFieldNotificationClassDescriptor::CurrentValueIndex, OnCurrentValueIndexChangedHandle);
}

void UDiscreteValueBase::HandleOnDiscreteValueAdded(UDiscreteValueViewModel* Item)
{
	OnDiscreteValueAdded(Item);
}

void UDiscreteValueBase::HandleOnDiscreteValueRemoved(UDiscreteValueViewModel* Item)
{
	OnDiscreteValueRemoved(Item);
}

void UDiscreteValueBase::OnCurrentValueIndexChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	OnDiscreteValueChanged();
}

void UDiscreteValueBase::OnDiscreteValueAdded_Implementation(UDiscreteValueViewModel* Item)
{
}

void UDiscreteValueBase::OnDiscreteValueRemoved_Implementation(UDiscreteValueViewModel* Item)
{
}

void UDiscreteValueBase::OnDiscreteValueChanged_Implementation()
{
}
