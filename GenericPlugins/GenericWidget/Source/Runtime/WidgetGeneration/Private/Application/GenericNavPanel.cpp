// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "Application/GenericNavPanel.h"

#include "WidgetType.h"
#include "Application/GenericNavBar.h"
#include "Application/GenericNavContent.h"
#include "Application/GenericNavViewModel.h"

UGenericNavViewModel* UGenericNavPanel::GetNavViewModel()
{
	return NavViewModel;
}

void UGenericNavPanel::SetNavViewModel(UGenericNavViewModel* InNavViewModel)
{
	if (NavViewModel)
	{
		NavViewModel->RemoveAllFieldValueChangedDelegates(this);
	}

	NavViewModel = InNavViewModel;

	if (NavBar)
	{
		NavBar->SetNavViewModel(NavViewModel);
	}

	if (NavContent)
	{
		NavContent->SetNavViewModel(NavViewModel);
	}
}
