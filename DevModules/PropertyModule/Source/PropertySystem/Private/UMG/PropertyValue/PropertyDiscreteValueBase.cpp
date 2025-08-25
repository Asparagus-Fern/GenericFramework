// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyValue/PropertyDiscreteValueBase.h"

#include "PropertyType.h"
#include "MVVM/Multi/MultiPropertyValueViewModel.h"

TSubclassOf<UPropertyValueViewModel> UPropertyDiscreteValueBase::GetSupportViewModelClass()
{
	return UMultiPropertyValueViewModel::StaticClass();
}

void UPropertyDiscreteValueBase::PostInitViewModelProperty()
{
	Super::PostInitViewModelProperty();

	if (UMultiPropertyValueViewModel* ViewModel = GetViewModel<UMultiPropertyValueViewModel>())
	{
		MultiPropertyValueViewModel = ViewModel;
	}
}

void UPropertyDiscreteValueBase::NativeOnViewModelInitialized()
{
	Super::NativeOnViewModelInitialized();

	if (MultiPropertyValueViewModel)
	{
		MultiPropertyValueViewModel->OnPropertyValueAddedEvent.AddUObject(this, &UPropertyDiscreteValueBase::HandleOnPropertyValueAdded);
		MultiPropertyValueViewModel->OnPropertyValueRemovedEvent.AddUObject(this, &UPropertyDiscreteValueBase::HandleOnPropertyValueRemoved);
		MVVM_REGISTRY(OnSelectedValueIndexChangedHandle, MultiPropertyValueViewModel, SelectedValueIndex, HandleOnSelectedValueIndexChanged)

		for (auto& Value : MultiPropertyValueViewModel->PropertyValues)
		{
			HandleOnPropertyValueAdded(Value);
		}

		OnSelectedValueIndexChanged(MultiPropertyValueViewModel->GetSelectedValue());
	}
}

void UPropertyDiscreteValueBase::NativeOnViewModelDeinitialized()
{
	Super::NativeOnViewModelDeinitialized();

	if (MultiPropertyValueViewModel)
	{
		MultiPropertyValueViewModel->OnPropertyValueAddedEvent.RemoveAll(this);
		MultiPropertyValueViewModel->OnPropertyValueRemovedEvent.RemoveAll(this);
		MVVM_UNREGISTRY(OnSelectedValueIndexChangedHandle, MultiPropertyValueViewModel, SelectedValueIndex)
	}
}

void UPropertyDiscreteValueBase::HandleOnPropertyValueAdded(USinglePropertyValueViewModel* ViewModel)
{
	OnPropertyValueAdded(ViewModel);
}

void UPropertyDiscreteValueBase::HandleOnPropertyValueRemoved(USinglePropertyValueViewModel* ViewModel)
{
	OnPropertyValueRemoved(ViewModel);
}

void UPropertyDiscreteValueBase::HandleOnSelectedValueIndexChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	OnSelectedValueIndexChanged(MultiPropertyValueViewModel->GetSelectedValue());
}

void UPropertyDiscreteValueBase::OnPropertyValueAdded_Implementation(USinglePropertyValueViewModel* ViewModel)
{
}

void UPropertyDiscreteValueBase::OnPropertyValueRemoved_Implementation(USinglePropertyValueViewModel* ViewModel)
{
}

void UPropertyDiscreteValueBase::OnSelectedValueIndexChanged_Implementation(USinglePropertyValueViewModel* ViewModel)
{
}
