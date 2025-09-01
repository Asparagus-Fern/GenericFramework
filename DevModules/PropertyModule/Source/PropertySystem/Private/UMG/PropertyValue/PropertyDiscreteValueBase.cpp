// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyValue/PropertyDiscreteValueBase.h"

#include "WidgetType.h"
#include "MVVM/Multi/MultiPropertyValueViewModel.h"

TSubclassOf<UPropertyValueViewModel> UPropertyDiscreteValueBase::GetSupportPropertyViewModelClass()
{
	return UMultiPropertyValueViewModel::StaticClass();
}

void UPropertyDiscreteValueBase::PostInitPropertyViewModel()
{
	Super::PostInitPropertyViewModel();

	if (UMultiPropertyValueViewModel* ViewModel = GetPropertyViewModel<UMultiPropertyValueViewModel>())
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

		for (auto& Value : MultiPropertyValueViewModel->PropertyValues)
		{
			HandleOnPropertyValueAdded(Value);
		}

		REGISTER_MVVM_PROPERTY(MultiPropertyValueViewModel, bAllowWrap, OnAllowWrapChanged, true)
		REGISTER_MVVM_PROPERTY(MultiPropertyValueViewModel, SelectedValueIndex, OnSelectedValueIndexChanged, true)
	}
}

void UPropertyDiscreteValueBase::NativeOnViewModelDeinitialized()
{
	Super::NativeOnViewModelDeinitialized();

	if (MultiPropertyValueViewModel)
	{
		MultiPropertyValueViewModel->OnPropertyValueAddedEvent.RemoveAll(this);
		MultiPropertyValueViewModel->OnPropertyValueRemovedEvent.RemoveAll(this);
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

void UPropertyDiscreteValueBase::OnAllowWrapChanged_Implementation(bool IsAllowWrap)
{
}

void UPropertyDiscreteValueBase::OnPropertyValueAdded_Implementation(USinglePropertyValueViewModel* ViewModel)
{
}

void UPropertyDiscreteValueBase::OnPropertyValueRemoved_Implementation(USinglePropertyValueViewModel* ViewModel)
{
}

void UPropertyDiscreteValueBase::OnSelectedValueIndexChanged_Implementation(int32 SelectedValueIndex)
{
}
