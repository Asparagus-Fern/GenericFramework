// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/DevPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Gameplay/Common/CommonPlayerCameraManager.h"
#include "Input/PlayerInputComponent.h"
#include "Pawn/PawnInterface.h"

ADevPlayerController::ADevPlayerController()
{
	PlayerCameraManagerClass = ACommonPlayerCameraManager::StaticClass();
}

// void ADevPlayerController::OnPossess(APawn* InPawn)
// {
// 	Super::OnPossess(InPawn);
//
// 	UPlayerInputComponent* PlayerInputComponent = Cast<UPlayerInputComponent>(InPawn->FindComponentByClass(UPlayerInputComponent::StaticClass()));
// 	if (IsValid(PlayerInputComponent))
// 	{
// 		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
// 		{
// 			for (auto& EnhanceInputMappingContext : PlayerInputComponent->EnhanceInputMappingContexts)
// 			{
// 				EnhancedInputLocalPlayerSubsystem->AddMappingContext(EnhanceInputMappingContext.InputMappingContext, EnhanceInputMappingContext.Priority, EnhanceInputMappingContext.ModifyContextOptions);
// 			}
// 		}
// 	}
// }
//
// void ADevPlayerController::OnUnPossess()
// {
// 	UActorComponent* ActorComponent = GetPawn()->FindComponentByClass(UPlayerInputComponent::StaticClass());
// 	if (IsValid(ActorComponent))
// 	{
// 		if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
// 		{
// 			for (const auto& EnhanceInputMappingContext : Cast<UPlayerInputComponent>(ActorComponent)->EnhanceInputMappingContexts)
// 			{
// 				EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(EnhanceInputMappingContext.InputMappingContext);
// 			}
// 		}
// 	}
//
// 	Super::OnUnPossess();
// }
