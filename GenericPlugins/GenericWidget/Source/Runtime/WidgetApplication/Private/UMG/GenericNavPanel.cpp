// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "UMG/GenericNavPanel.h"

#include "MVVM/GenericNavViewModel.h"
#include "UMG/GenericNavBar.h"
#include "UMG/GenericNavContent.h"

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
