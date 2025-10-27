// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "BPFunctions_Window.h"

#include "GenericWindowManager.h"

UGenericWindowWrapper* UBPFunctions_Window::RegisterWindowWrapperByClass(APlayerController* InPlayer, const TSubclassOf<UGenericWindowViewModel>& WindowViewModelClass, bool& Result)
{
	return FWindowHelper::RegisterWindowWrapper(InPlayer, WindowViewModelClass, Result);
}

UGenericWindowWrapper* UBPFunctions_Window::RegisterWindowWrapper(APlayerController* InPlayer, UGenericWindowViewModel* WindowViewModel, bool& Result)
{
	return FWindowHelper::RegisterWindowWrapper(InPlayer, WindowViewModel, Result);
}

bool UBPFunctions_Window::UnRegisterWindowWrapper(UGenericWindowWrapper* InWrapper)
{
	return FWindowHelper::UnRegisterWindowWrapper(InWrapper);
}

void UBPFunctions_Window::UnRegisterAllWindowWrapper()
{
	FWindowHelper::UnRegisterAllWindowWrapper();
}
