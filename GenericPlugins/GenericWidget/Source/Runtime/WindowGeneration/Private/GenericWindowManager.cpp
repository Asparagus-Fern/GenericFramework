// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericWindowManager.h"

#include "GenericWindowType.h"
#include "GenericWindowViewModel.h"
#include "GenericWindowWrapper.h"

bool UGenericWindowManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGenericWindowManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UGenericWindowManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterAllWindowWrapper();
	UnRegisterManager();
}

UGenericWindowWrapper* UGenericWindowManager::RegisterWindowWrapper(APlayerController* InPlayer, const TSubclassOf<UGenericWindowViewModel>& WindowViewModelClass, bool& Result)
{
	if (!WindowViewModelClass)
	{
		GenericLOG(GenericLogWindow, Error, TEXT("WindowViewModelClass Is InValid"))
		return nullptr;
	}

	UGenericWindowViewModel* WindowViewModel = NewObject<UGenericWindowViewModel>(InPlayer, WindowViewModelClass);
	UGenericWindowWrapper* WindowWrapper = RegisterWindowWrapper(InPlayer, WindowViewModel, Result);

	if (!Result)
	{
		WindowViewModel->MarkAsGarbage();
		return nullptr;
	}

	return WindowWrapper;
}

UGenericWindowWrapper* UGenericWindowManager::RegisterWindowWrapper(APlayerController* InPlayer, UGenericWindowViewModel* WindowViewModel, bool& Result)
{
	Result = false;

	if (!InPlayer)
	{
		GenericLOG(GenericLogWindow, Error, TEXT("Player Is InValid"))
		return nullptr;
	}

	if (!IsValid(WindowViewModel))
	{
		GenericLOG(GenericLogWindow, Error, TEXT("WindowViewModel Is InValid"))
		return nullptr;
	}

	UGenericWindowWrapper* NewWindowWrapper = NewObject<UGenericWindowWrapper>(InPlayer);

	if (!NewWindowWrapper->Initialize(WindowViewModel))
	{
		GenericLOG(GenericLogWindow, Error, TEXT("Wrapper Initialize Fail"))
		NewWindowWrapper->MarkAsGarbage();
		return nullptr;
	}

	Result = true;
	WindowWrappers.Add(NewWindowWrapper);
	return NewWindowWrapper;
}

bool UGenericWindowManager::UnRegisterWindowWrapper(UGenericWindowWrapper* InWrapper)
{
	if (!IsValid(InWrapper))
	{
		GenericLOG(GenericLogWindow, Error, TEXT("InWrapper Is InValid"))
		return false;
	}

	if (!WindowWrappers.Contains(InWrapper))
	{
		GenericLOG(GenericLogWindow, Error, TEXT("InWrapper Is Already Unregister"))
		return false;
	}

	InWrapper->Deinitialize();
	WindowWrappers.Remove(InWrapper);
	return true;
}

void UGenericWindowManager::UnRegisterAllWindowWrapper()
{
	TArray<UGenericWindowWrapper*> TempWindowWrappers = WindowWrappers;
	for (const auto& TempWindowWrapper : TempWindowWrappers)
	{
		UnRegisterWindowWrapper(TempWindowWrapper);
	}
}

UGenericWindowWrapper* FWindowHelper::RegisterWindowWrapper(APlayerController* InPlayer, const TSubclassOf<UGenericWindowViewModel>& WindowViewModelClass, bool& Result)
{
	if (UGenericWindowManager* GenericWindowManager = GetManagerOwner<UGenericWindowManager>())
	{
		return GenericWindowManager->RegisterWindowWrapper(InPlayer, WindowViewModelClass, Result);
	}
	return nullptr;
}

UGenericWindowWrapper* FWindowHelper::RegisterWindowWrapper(APlayerController* InPlayer, UGenericWindowViewModel* WindowViewModel, bool& Result)
{
	if (UGenericWindowManager* GenericWindowManager = GetManagerOwner<UGenericWindowManager>())
	{
		return GenericWindowManager->RegisterWindowWrapper(InPlayer, WindowViewModel, Result);
	}
	return nullptr;
}

bool FWindowHelper::UnRegisterWindowWrapper(UGenericWindowWrapper* InWrapper)
{
	if (UGenericWindowManager* GenericWindowManager = GetManagerOwner<UGenericWindowManager>())
	{
		return GenericWindowManager->UnRegisterWindowWrapper(InWrapper);
	}
	return false;
}

void FWindowHelper::UnRegisterAllWindowWrapper()
{
	if (UGenericWindowManager* GenericWindowManager = GetManagerOwner<UGenericWindowManager>())
	{
		return GenericWindowManager->UnRegisterAllWindowWrapper();
	}
}
