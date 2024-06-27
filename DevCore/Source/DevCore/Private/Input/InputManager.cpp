// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputManager.h"

#include "EnhancedInputSubsystems.h"

#define LOCTEXT_NAMESPACE "UInputManager"

UInputManager::UInputManager()
{
	// DisplayName = LOCTEXT("DisplayName", "Input Manager");
	// ProcedureOrder = -1;
}

void UInputManager::NativeOnActived()
{
	Super::NativeOnActived();

	if (const APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			for (auto& EnhanceInputMappingContext : EnhanceInputMappingContexts)
			{
				EnhancedInputLocalPlayerSubsystem->AddMappingContext(EnhanceInputMappingContext.InputMappingContext, EnhanceInputMappingContext.Priority, EnhanceInputMappingContext.ModifyContextOptions);
			}
		}
	}
}

void UInputManager::NativeOnInactived()
{
	Super::NativeOnInactived();
}

#undef LOCTEXT_NAMESPACE
