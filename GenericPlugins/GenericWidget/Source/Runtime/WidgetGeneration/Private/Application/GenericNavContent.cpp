// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "Application/GenericNavContent.h"

#include "WidgetType.h"
#include "Application/GenericNavViewModel.h"

void UGenericNavContent::NativeConstruct()
{
	Super::NativeConstruct();

	REGISTER_MVVM_PROPERTY(NavViewModel, NavNum, OnNavNumChanged, true)
	REGISTER_MVVM_PROPERTY(NavViewModel, NavIndex, OnNavIndexChanged, true)
}

void UGenericNavContent::NativeDestruct()
{
	Super::NativeDestruct();

	UNREGISTER_MVVM_PROPERTY(NavViewModel)
}

UGenericNavViewModel* UGenericNavContent::GetNavViewModel()
{
	return NavViewModel;
}

void UGenericNavContent::SetNavViewModel(UGenericNavViewModel* InNavViewModel)
{
	if (NavViewModel)
	{
		NavViewModel->RemoveAllFieldValueChangedDelegates(this);
	}

	NavViewModel = InNavViewModel;

	if (NavViewModel)
	{
		REGISTER_MVVM_PROPERTY(NavViewModel, NavNum, OnNavNumChanged, true)
		REGISTER_MVVM_PROPERTY(NavViewModel, NavIndex, OnNavIndexChanged, true)
	}
}

void UGenericNavContent::OnNavNumChanged_Implementation(int32 InNum)
{
}

void UGenericNavContent::OnNavIndexChanged_Implementation(int32 InIndex)
{
}
