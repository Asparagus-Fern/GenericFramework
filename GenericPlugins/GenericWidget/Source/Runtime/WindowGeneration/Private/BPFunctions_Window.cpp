// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "BPFunctions_Window.h"

#include "GenericWindowSubsystem.h"

UGenericWindowWrapper* UBPFunctions_Window::RegisterWindowWrapperByClass(const UObject* WorldContextObject, APlayerController* InPlayer, const TSubclassOf<UGenericWindowViewModel>& WindowViewModelClass, bool& Result)
{
	if (UGenericWindowSubsystem* GenericWindowSubsystem = UGenericWindowSubsystem::Get(WorldContextObject))
	{
		return GenericWindowSubsystem->RegisterWindowWrapper(InPlayer, WindowViewModelClass, Result);
	}
	return nullptr;
}

UGenericWindowWrapper* UBPFunctions_Window::RegisterWindowWrapper(const UObject* WorldContextObject, APlayerController* InPlayer, UGenericWindowViewModel* WindowViewModel, bool& Result)
{
	if (UGenericWindowSubsystem* GenericWindowSubsystem = UGenericWindowSubsystem::Get(WorldContextObject))
	{
		return GenericWindowSubsystem->RegisterWindowWrapper(InPlayer, WindowViewModel, Result);
	}
	return nullptr;
}

bool UBPFunctions_Window::UnRegisterWindowWrapper(const UObject* WorldContextObject, UGenericWindowWrapper* InWrapper)
{
	if (UGenericWindowSubsystem* GenericWindowSubsystem = UGenericWindowSubsystem::Get(WorldContextObject))
	{
		return GenericWindowSubsystem->UnRegisterWindowWrapper(InWrapper);
	}
	return false;
}

void UBPFunctions_Window::UnRegisterAllWindowWrapper(const UObject* WorldContextObject)
{
	if (UGenericWindowSubsystem* GenericWindowSubsystem = UGenericWindowSubsystem::Get(WorldContextObject))
	{
		GenericWindowSubsystem->UnRegisterAllWindowWrapper();
	}
}
