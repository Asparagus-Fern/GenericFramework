// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputManager.h"

#include "EnhancedInputSubsystems.h"
#include "Input/InputManagerSetting.h"

#define LOCTEXT_NAMESPACE "UInputManager"

bool UInputManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UInputManagerSetting::Get()->bEnableSubsystem;
}

void UInputManager::NativeOnActived()
{
	Super::NativeOnActived();

	if (const APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			for (auto& EnhanceInputMappingContext : UInputManagerSetting::Get()->EnhanceInputMappingContexts)
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
