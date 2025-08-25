// Copyright ChenTaiye 2025. All Rights Reserved.


#include "UMG/PropertyValue/PropertyValueBase.h"

#include "PropertyType.h"

void UPropertyValueBase::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPropertyValueBase::NativeDestruct()
{
	Super::NativeDestruct();

	NativeOnViewModelDeinitialized();
	OnViewModelDeinitialized();
}

UPropertyValueViewModel* UPropertyValueBase::BP_GetViewModel(TSubclassOf<UPropertyValueViewModel> InClass)
{
	ensure(InClass);
	return GetViewModel<UPropertyValueViewModel>();
}

void UPropertyValueBase::BP_SetViewModel(UPropertyValueViewModel* InViewModel)
{
	SetViewModel(InViewModel);
}

void UPropertyValueBase::NativeOnViewModelInitialized()
{
}

void UPropertyValueBase::NativeOnViewModelDeinitialized()
{
}
