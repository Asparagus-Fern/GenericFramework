// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "GenericWindowManager.h"

#include "GenericMessageDialog.h"
#include "GenericWindowType.h"
#include "GenericWindowViewModel.h"
#include "GenericWindowWrapper.h"
#include "MessageDialogSettings.h"
#include "Blueprint/UserWidget.h"
#include "StaticFunctions/StaticFunctions_Object.h"

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

FGameplayTag UGenericWindowManager::OpenMessageDialog(APlayerController* InPlayer, const TSubclassOf<UGenericMessageDialog>& MessageDialogClass, bool& Result)
{
	if (!IsValid(InPlayer))
	{
		GenericLOG(GenericLogWindow, Error, TEXT("Player Is InValid"))
		return FGameplayTag::EmptyTag;
	}

	if (!MessageDialogClass)
	{
		GenericLOG(GenericLogWindow, Error, TEXT("MessageDialogClass Is InValid"))
		return FGameplayTag::EmptyTag;
	}

	UGenericMessageDialog* NewMessageDialog = CreateWidget<UGenericMessageDialog>(InPlayer, MessageDialogClass);
	FGameplayTag ResultDialogType = OpenMessageDialog(InPlayer, NewMessageDialog, Result);

	if (!Result)
	{
		NewMessageDialog->MarkAsGarbage();
		return FGameplayTag::EmptyTag;
	}

	return ResultDialogType;
}

FGameplayTag UGenericWindowManager::OpenMessageDialog(APlayerController* InPlayer, UGenericMessageDialog* MessageDialog, bool& Result)
{
	FGameplayTag ResultDialogType;

	if (!IsValid(InPlayer))
	{
		GenericLOG(GenericLogWindow, Error, TEXT("Player Is InValid"))
		return ResultDialogType;
	}

	if (!UMessageDialogSettings::Get()->MessageDialogWindowClass)
	{
		GenericLOG(GenericLogWindow, Error, TEXT("MessageDialogWindowClass Is InValid"))
		return ResultDialogType;
	}

	TSubclassOf<UGenericWindowViewModel> WindowClass = FStaticFunctions_Object::LoadClass<UGenericWindowViewModel>(UMessageDialogSettings::Get()->MessageDialogWindowClass);
	UGenericWindowViewModel* MessageDialogWindowViewModel = NewObject<UGenericWindowViewModel>(InPlayer, WindowClass);

	/* Register Window Wrapper */
	UGenericWindowWrapper* Wrapper = RegisterWindowWrapper(InPlayer, MessageDialogWindowViewModel, Result);
	if (Result)
	{
		Wrapper->SetWindowContentObject(MessageDialog);

		/* If This Window Is a Modal Window, Will Break Game Thread Here */
		Wrapper->OpenWindow();

		/* Return The Result And Unregister It */
		ResultDialogType = MessageDialog->GetResultDialogType();
		UnRegisterWindowWrapper(Wrapper);
	}
	else
	{
		GenericLOG(GenericLogWindow, Error, TEXT("Fail To Open Message Dialog"))
		MessageDialogWindowViewModel->MarkAsGarbage();
	}

	return ResultDialogType;
}
