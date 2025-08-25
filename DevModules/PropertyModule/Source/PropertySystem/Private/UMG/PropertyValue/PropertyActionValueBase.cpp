// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyValue/PropertyActionValueBase.h"

#include "MVVM/Action/ActionPropertyValueViewModel.h"

TSubclassOf<UPropertyValueViewModel> UPropertyActionValueBase::GetSupportViewModelClass()
{
	return UActionPropertyValueViewModel::StaticClass();
}

void UPropertyActionValueBase::PostInitViewModelProperty()
{
	Super::PostInitViewModelProperty();

	if (UActionPropertyValueViewModel* ViewModel = GetViewModel<UActionPropertyValueViewModel>())
	{
		ActionPropertyValueViewModel = ViewModel;
	}
}

void UPropertyActionValueBase::NativeOnViewModelInitialized()
{
	Super::NativeOnViewModelInitialized();
}

void UPropertyActionValueBase::NativeOnViewModelDeinitialized()
{
	Super::NativeOnViewModelDeinitialized();
}
