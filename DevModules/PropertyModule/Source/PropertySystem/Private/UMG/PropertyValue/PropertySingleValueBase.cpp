// Copyright ChenTaiye 2025. All Rights Reserved.


#include "UMG/PropertyValue/PropertySingleValueBase.h"

#include "PropertyType.h"
#include "MVVM/Single/SinglePropertyValueViewModel.h"

TSubclassOf<UPropertyValueViewModel> UPropertySingleValueBase::GetSupportViewModelClass()
{
	return USinglePropertyValueViewModel::StaticClass();;
}

void UPropertySingleValueBase::PostInitViewModelProperty()
{
	Super::PostInitViewModelProperty();
}

void UPropertySingleValueBase::NativeOnViewModelInitialized()
{
	Super::NativeOnViewModelInitialized();

	if (USinglePropertyValueViewModel* ViewModel = GetViewModel<USinglePropertyValueViewModel>())
	{
		MVVM_REGISTRY(OnPropertyValueNameChangedHandle, ViewModel, PropertyValueName, HandleOnPropertyValueNameChanged)
		MVVM_REGISTRY(OnPropertyValueDisplayNameChangedHandle, ViewModel, PropertyValueDisplayName, HandleOnPropertyValueDisplayNameChanged)
		MVVM_REGISTRY(OnPropertyValueTooltipChangedHandle, ViewModel, PropertyValueTooltip, HandleOnPropertyValueTooltipChanged)
	}
}

void UPropertySingleValueBase::NativeOnViewModelDeinitialized()
{
	Super::NativeOnViewModelDeinitialized();

	if (USinglePropertyValueViewModel* ViewModel = GetViewModel<USinglePropertyValueViewModel>())
	{
		MVVM_UNREGISTRY(OnPropertyValueNameChangedHandle, ViewModel, PropertyValueName)
		MVVM_UNREGISTRY(OnPropertyValueDisplayNameChangedHandle, ViewModel, PropertyValueDisplayName)
		MVVM_UNREGISTRY(OnPropertyValueTooltipChangedHandle, ViewModel, PropertyValueTooltip)
	}
}

void UPropertySingleValueBase::HandleOnPropertyValueNameChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	USinglePropertyValueViewModel* ViewModel = GetViewModel<USinglePropertyValueViewModel>();
	OnPropertyValueNameChanged(ViewModel->PropertyValueName);
}

void UPropertySingleValueBase::HandleOnPropertyValueDisplayNameChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	USinglePropertyValueViewModel* ViewModel = GetViewModel<USinglePropertyValueViewModel>();
	OnPropertyValueDisplayNameChanged(ViewModel->PropertyValueDisplayName);
}

void UPropertySingleValueBase::HandleOnPropertyValueTooltipChanged(UObject* InObject, UE::FieldNotification::FFieldId InFieldId)
{
	USinglePropertyValueViewModel* ViewModel = GetViewModel<USinglePropertyValueViewModel>();
	OnPropertyValueTooltipChanged(ViewModel->PropertyValueTooltip);
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
