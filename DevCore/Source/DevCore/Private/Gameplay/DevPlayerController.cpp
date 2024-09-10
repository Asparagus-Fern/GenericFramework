// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/DevPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Gameplay/Common/CommonPlayerCameraManager.h"
#include "Input/InputHandleComponent.h"
#include "Pawn/PawnInterface.h"

ADevPlayerController::ADevPlayerController()
{
	PlayerCameraManagerClass = ACommonPlayerCameraManager::StaticClass();
}

void ADevPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UActorComponent* ActorComponent = InPawn->FindComponentByClass(UInputHandleComponent::StaticClass());
	if (IsValid(ActorComponent))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			for (auto& EnhanceInputMappingContext : Cast<UInputHandleComponent>(ActorComponent)->EnhanceInputMappingContexts)
			{
				EnhancedInputLocalPlayerSubsystem->AddMappingContext(EnhanceInputMappingContext.InputMappingContext, EnhanceInputMappingContext.Priority, EnhanceInputMappingContext.ModifyContextOptions);
			}
		}
	}
}

void ADevPlayerController::OnUnPossess()
{
	UActorComponent* ActorComponent = GetPawn()->FindComponentByClass(UInputHandleComponent::StaticClass());
	if (IsValid(ActorComponent))
	{
		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			for (const auto& EnhanceInputMappingContext : Cast<UInputHandleComponent>(ActorComponent)->EnhanceInputMappingContexts)
			{
				EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(EnhanceInputMappingContext.InputMappingContext);
			}
		}
	}

	Super::OnUnPossess();
}
