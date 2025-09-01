// Copyright ChenTaiye 2025. All Rights Reserved.


#include "UMG/PropertyValue/PropertySingleValueBase.h"

#include "WidgetType.h"
#include "MVVM/Single/SinglePropertyValueViewModel.h"

TSubclassOf<UPropertyValueViewModel> UPropertySingleValueBase::GetSupportPropertyViewModelClass()
{
	return USinglePropertyValueViewModel::StaticClass();;
}

void UPropertySingleValueBase::PostInitPropertyViewModel()
{
	Super::PostInitPropertyViewModel();
}

void UPropertySingleValueBase::NativeOnViewModelInitialized()
{
	Super::NativeOnViewModelInitialized();

	if (USinglePropertyValueViewModel* ViewModel = GetPropertyViewModel<USinglePropertyValueViewModel>())
	{
		REGISTER_MVVM_PROPERTY(ViewModel, PropertyValueName, OnPropertyValueNameChanged, true)
		REGISTER_MVVM_PROPERTY(ViewModel, PropertyValueDisplayName, OnPropertyValueDisplayNameChanged, true)
		REGISTER_MVVM_PROPERTY(ViewModel, PropertyValueTooltip, OnPropertyValueTooltipChanged, true)
	}
}

void UPropertySingleValueBase::NativeOnViewModelDeinitialized()
{
	Super::NativeOnViewModelDeinitialized();
}

void UPropertySingleValueBase::OnPropertyValueNameChanged_Implementation(FName InName)
{
}

void UPropertySingleValueBase::OnPropertyValueDisplayNameChanged_Implementation(const FText& InDisplayName)
{
}

void UPropertySingleValueBase::OnPropertyValueTooltipChanged_Implementation(const FText& InTooltip)
{
}
