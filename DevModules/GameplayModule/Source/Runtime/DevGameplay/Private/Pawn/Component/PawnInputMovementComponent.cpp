// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/Component/PawnInputMovementComponent.h"

#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pawn/Component/PawnLockStateComponent.h"

IPawnInputMovementInterface::IPawnInputMovementInterface()
{
}

UPawnInputMovementComponent::UPawnInputMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPawnInputMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	SetupPlayerInput();
}

void UPawnInputMovementComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	RemovePlayerInput();
}

void UPawnInputMovementComponent::AddLocation_Implementation(FVector2D InValue)
{
	if (APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		if (Pawn->GetClass()->ImplementsInterface(UPawnLockStateInterface::StaticClass()))
		{
			if (!IPawnLockStateInterface::Execute_CanMove(GetOwner(), Pawn->GetActorLocation()))
			{
				return;
			}
		}

		const FVector2D Movement = InValue * MovementSpeedRate;
		Pawn->AddMovementInput(UKismetMathLibrary::GetRightVector(Pawn->GetActorRotation()), Movement.X);
		Pawn->AddMovementInput(UKismetMathLibrary::GetForwardVector(Pawn->GetActorRotation()), Movement.Y);
	}
}

void UPawnInputMovementComponent::AddRotation_Implementation(FVector2D InValue)
{
	if (APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		if (Pawn->GetClass()->ImplementsInterface(UPawnLockStateInterface::StaticClass()))
		{
			if (!IPawnLockStateInterface::Execute_CanTurn(GetOwner(), Pawn->GetActorRotation()))
			{
				return;
			}
		}

		const FVector2D Rotation = InValue * RotationSpeedRate;
		Pawn->AddControllerYawInput(Rotation.X);
		Pawn->AddControllerPitchInput(Rotation.Y);
	}
}

void UPawnInputMovementComponent::AddZoom_Implementation(float InValue)
{
}

void UPawnInputMovementComponent::SetLocation_Implementation(FVector InValue)
{
	if (GetOwner()->GetClass()->ImplementsInterface(UPawnLockStateInterface::StaticClass()))
	{
		if (!IPawnLockStateInterface::Execute_CanMove(GetOwner(), GetOwner()->GetActorLocation()))
		{
			return;
		}
	}

	GetOwner()->SetActorLocation(InValue);
}

void UPawnInputMovementComponent::SetRotation_Implementation(FRotator InValue)
{
	if (GetOwner()->GetClass()->ImplementsInterface(UPawnLockStateInterface::StaticClass()))
	{
		if (!IPawnLockStateInterface::Execute_CanTurn(GetOwner(), GetOwner()->GetActorRotation()))
		{
			return;
		}
	}

	GetOwner()->SetActorRotation(InValue);
}

void UPawnInputMovementComponent::SetZoom_Implementation(float InValue)
{
}

FVector UPawnInputMovementComponent::GetLocation_Implementation()
{
	return GetOwner()->GetActorLocation();
}

FRotator UPawnInputMovementComponent::GetRotation_Implementation()
{
	return GetOwner()->GetActorRotation();
}

float UPawnInputMovementComponent::GetZoom_Implementation()
{
	return -1.f;
}

float UPawnInputMovementComponent::GetMovementSpeedRate_Implementation()
{
	return MovementSpeedRate;
}

float UPawnInputMovementComponent::GetRotationSpeedRate_Implementation()
{
	return RotationSpeedRate;
}

float UPawnInputMovementComponent::GetZoomSpeedRate_Implementation()
{
	return ZoomSpeedRate;
}

void UPawnInputMovementComponent::SetupPlayerInput_Implementation()
{
	if (const APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		const APlayerController* PC = Cast<APlayerController>(Pawn->Controller);
		if (IsValid(PC))
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
}

void UPawnInputMovementComponent::RemovePlayerInput_Implementation()
{
	if (const APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		const APlayerController* PC = Cast<APlayerController>(Pawn->Controller);
		if (IsValid(PC))
		{
			if (UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = PC->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				for (const auto& EnhanceInputMappingContext : EnhanceInputMappingContexts)
				{
					EnhancedInputLocalPlayerSubsystem->RemoveMappingContext(EnhanceInputMappingContext.InputMappingContext);
				}
			}
		}
	}
}
