// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyValue/PropertyValueBase.h"

#include "WidgetType.h"

void UPropertyValueBase::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPropertyValueBase::NativeDestruct()
{
	Super::NativeDestruct();
	UNREGISTER_MVVM_PROPERTY(PropertyViewModel);
}

UPropertyViewModel* UPropertyValueBase::BP_GetPropertyViewModel(TSubclassOf<UPropertyViewModel> InClass)
{
	ensure(InClass);
	return GetPropertyViewModel<UPropertyViewModel>();
}

void UPropertyValueBase::BP_SetPropertyViewModel(UPropertyViewModel* InViewModel)
{
	SetPropertyViewModel(InViewModel);
}

TSubclassOf<UPropertyViewModel> UPropertyValueBase::GetSupportPropertyViewModelClass()
{
	return UPropertyViewModel::StaticClass();
}

void UPropertyValueBase::PreInitPropertyViewModel()
{
}

void UPropertyValueBase::PostInitPropertyViewModel()
{
}

void UPropertyValueBase::NativeOnViewModelInitialized()
{
	if (UPropertyViewModel* ViewModel = GetPropertyViewModel<UPropertyViewModel>())
	{
		REGISTER_MVVM_PROPERTY(ViewModel, IsDirtyProxy, OnIsDirtyProxyChanged, true)
		REGISTER_MVVM_PROPERTY(ViewModel, PropertyName, OnPropertyNameChanged, true)
		REGISTER_MVVM_PROPERTY(ViewModel, PropertyDisplayName, OnPropertyDisplayNameChanged, true)
		REGISTER_MVVM_PROPERTY(ViewModel, PropertyDescription, OnPropertyDescriptionChanged, true)
	}
}

void UPropertyValueBase::NativeOnViewModelDeinitialized()
{
}

void UPropertyValueBase::OnIsDirtyProxyChanged_Implementation(bool InIsDirtyProxy)
{
}

void UPropertyValueBase::OnPropertyNameChanged_Implementation(FName InPropertyName)
{
}

void UPropertyValueBase::OnPropertyDisplayNameChanged_Implementation(const FText& InPropertyDisplayName)
{
}

void UPropertyValueBase::OnPropertyDescriptionChanged_Implementation(const FText& InPropertyDescription)
{
}
