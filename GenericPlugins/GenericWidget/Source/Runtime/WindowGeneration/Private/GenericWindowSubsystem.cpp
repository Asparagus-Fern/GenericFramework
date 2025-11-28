// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericWindowSubsystem.h"

#include "GenericWindowType.h"
#include "GenericWindowViewModel.h"
#include "GenericWindowWrapper.h"

UGenericWindowSubsystem* UGenericWindowSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetGameInstance()->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

bool UGenericWindowSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && !IsRunningDedicatedServer();
}

void UGenericWindowSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UGenericWindowSubsystem::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterAllWindowWrapper();
}

UGenericWindowWrapper* UGenericWindowSubsystem::RegisterWindowWrapper(APlayerController* InPlayer, const TSubclassOf<UGenericWindowViewModel>& WindowViewModelClass, bool& Result)
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

UGenericWindowWrapper* UGenericWindowSubsystem::RegisterWindowWrapper(APlayerController* InPlayer, UGenericWindowViewModel* WindowViewModel, bool& Result)
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

bool UGenericWindowSubsystem::UnRegisterWindowWrapper(UGenericWindowWrapper* InWrapper)
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

void UGenericWindowSubsystem::UnRegisterAllWindowWrapper()
{
	TArray<UGenericWindowWrapper*> TempWindowWrappers = WindowWrappers;
	for (const auto& TempWindowWrapper : TempWindowWrappers)
	{
		UnRegisterWindowWrapper(TempWindowWrapper);
	}
}
