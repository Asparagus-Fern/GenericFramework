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

	UNREGISTER_MVVM_PROPERTY(PropertyValueViewModel);
}

UPropertyValueViewModel* UPropertyValueBase::BP_GetPropertyViewModel(TSubclassOf<UPropertyValueViewModel> InClass)
{
	ensure(InClass);
	return GetPropertyViewModel<UPropertyValueViewModel>();
}

void UPropertyValueBase::BP_SetPropertyViewModel(UPropertyValueViewModel* InViewModel)
{
	SetPropertyViewModel(InViewModel);
}

void UPropertyValueBase::NativeOnViewModelInitialized()
{
}

void UPropertyValueBase::NativeOnViewModelDeinitialized()
{
}
