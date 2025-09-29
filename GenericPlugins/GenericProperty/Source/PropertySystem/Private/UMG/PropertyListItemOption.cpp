// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "UMG/PropertyListItemOption.h"

#include "MVVM/PropertyViewModel.h"

void UPropertyListItemOption::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPropertyListItemOption::NativeDestruct()
{
	Super::NativeDestruct();

	if (PropertyViewModel.IsValid())
	{
		PropertyViewModel.Get()->RemoveAllFieldValueChangedDelegates(this);
	}
}

void UPropertyListItemOption::SetPropertyViewModel(UPropertyViewModel* InViewModel)
{
	if (PropertyViewModel.IsValid())
	{
		PropertyViewModel.Get()->RemoveAllFieldValueChangedDelegates(this);
	}

	PropertyViewModel = InViewModel;

	if (InViewModel)
	{
		InViewModel->GetOnPropertyApplyEvent().AddUFunction(this,GET_FUNCTION_NAME_CHECKED(UPropertyListItemOption, OnPropertyApply));
		InViewModel->GetOnPropertyResetEvent().AddUFunction(this,GET_FUNCTION_NAME_CHECKED(UPropertyListItemOption, OnPropertyReset));
		InViewModel->GetOnPropertyChangedEvent().AddUFunction(this,GET_FUNCTION_NAME_CHECKED(UPropertyListItemOption, OnPropertyValueChanged));

		OnPropertyViewModelInitialized(InViewModel);
	}
}

void UPropertyListItemOption::OnPropertyViewModelInitialized_Implementation(UPropertyViewModel* InViewModel)
{
}

void UPropertyListItemOption::OnPropertyApply_Implementation(UPropertyViewModel* InViewModel)
{
}

void UPropertyListItemOption::OnPropertyReset_Implementation(UPropertyViewModel* InViewModel)
{
}

void UPropertyListItemOption::OnPropertyValueChanged_Implementation(UPropertyViewModel* InViewModel, EPropertyChangedReason ChangedReason)
{
}
