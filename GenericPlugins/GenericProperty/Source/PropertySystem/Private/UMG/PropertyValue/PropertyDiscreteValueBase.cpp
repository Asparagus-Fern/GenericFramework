// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyValue/PropertyDiscreteValueBase.h"

#include "WidgetType.h"
#include "MVVM/Data/Multi/MultiPropertyValueViewModel.h"

TSubclassOf<UPropertyViewModel> UPropertyDiscreteValueBase::GetSupportPropertyViewModelClass()
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
		for (auto& Value : MultiPropertyValueViewModel->PropertyValues)
		{
			HandleOnPropertyValueAdded(Value.Key, Value.Value);
		}

		MultiPropertyValueViewModel->OnPropertyValueAddedEvent.AddUObject(this, &UPropertyDiscreteValueBase::HandleOnPropertyValueAdded);
		MultiPropertyValueViewModel->OnPropertyValueRemovedEvent.AddUObject(this, &UPropertyDiscreteValueBase::HandleOnPropertyValueRemoved);

		REGISTER_MVVM_PROPERTY(MultiPropertyValueViewModel, bAllowWrap, OnAllowWrapChanged, true)
		REGISTER_MVVM_PROPERTY(MultiPropertyValueViewModel, InitialValue, OnInitialValueChanged, true)
		REGISTER_MVVM_PROPERTY(MultiPropertyValueViewModel, SelectedValue, OnSelectedValueChanged, true)
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

void UPropertyDiscreteValueBase::HandleOnPropertyValueAdded(const FString& InName, UPropertyViewModel* InViewModel)
{
	OnPropertyValueAdded(InName, InViewModel);
}

void UPropertyDiscreteValueBase::HandleOnPropertyValueRemoved(const FString& InName, UPropertyViewModel* InViewModel)
{
	OnPropertyValueRemoved(InName, InViewModel);
}

void UPropertyDiscreteValueBase::OnInitialValueChanged_Implementation(const FString& InInitialValue)
{
}

void UPropertyDiscreteValueBase::OnAllowWrapChanged_Implementation(bool IsAllowWrap)
{
}

void UPropertyDiscreteValueBase::OnPropertyValueAdded_Implementation(const FString& InName, UPropertyViewModel* InViewModel)
{
}

void UPropertyDiscreteValueBase::OnPropertyValueRemoved_Implementation(const FString& InName, UPropertyViewModel* InViewModel)
{
}

void UPropertyDiscreteValueBase::OnSelectedValueChanged_Implementation(const FString& InSelectedValue)
{
}
