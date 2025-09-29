// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "Application/GenericNavBar.h"

#include "WidgetType.h"
#include "Application/GenericNavViewModel.h"
#include "Components/Button.h"
#include "Type/DebugType.h"

void UGenericNavBar::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button_Left)
	{
		Button_Left->OnClicked.AddUniqueDynamic(this, &UGenericNavBar::SwitchLeft);
	}

	if (Button_Right)
	{
		Button_Right->OnClicked.AddUniqueDynamic(this, &UGenericNavBar::SwitchRight);
	}

	if (NavViewModel)
	{
		REGISTER_MVVM_PROPERTY(NavViewModel, NavNum, OnNavNumChanged, true)
		REGISTER_MVVM_PROPERTY(NavViewModel, NavIndex, OnNavIndexChanged, true)
	}
}

void UGenericNavBar::NativeDestruct()
{
	Super::NativeDestruct();

	if (Button_Left)
	{
		Button_Left->OnClicked.RemoveAll(this);
	}

	if (Button_Right)
	{
		Button_Right->OnClicked.RemoveAll(this);
	}
}

void UGenericNavBar::SwitchLeft()
{
	if (NavViewModel)
	{
		NavViewModel->SwitchLeft();
	}
}

void UGenericNavBar::SwitchRight()
{
	if (NavViewModel)
	{
		NavViewModel->SwitchRight();
	}
}

UGenericNavViewModel* UGenericNavBar::GetNavViewModel()
{
	return NavViewModel;
}

void UGenericNavBar::SetNavViewModel(UGenericNavViewModel* InNavViewModel)
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

void UGenericNavBar::OnNavNumChanged_Implementation(int32 InNum)
{
}

void UGenericNavBar::OnNavIndexChanged_Implementation(int32 InIndex)
{
}
