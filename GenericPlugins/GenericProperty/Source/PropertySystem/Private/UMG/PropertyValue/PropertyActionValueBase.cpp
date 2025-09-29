// Copyright ChenTaiye 2025. All Rights Reserved.

#include "UMG/PropertyValue/PropertyActionValueBase.h"

#include "MVVM/Action/ActionPropertyValueViewModel.h"

TSubclassOf<UPropertyViewModel> UPropertyActionValueBase::GetSupportPropertyViewModelClass()
{
	return UActionPropertyValueViewModel::StaticClass();
}

void UPropertyActionValueBase::PostInitPropertyViewModel()
{
	Super::PostInitPropertyViewModel();

	if (UActionPropertyValueViewModel* ViewModel = GetPropertyViewModel<UActionPropertyValueViewModel>())
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
