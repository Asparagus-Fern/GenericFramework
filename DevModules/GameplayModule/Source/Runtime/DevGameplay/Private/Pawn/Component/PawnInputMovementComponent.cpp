// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Pawn/Component/PawnInputMovementComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Pawn/Component/PawnLockStateComponent.h"

IPawnInputMovementInterface::IPawnInputMovementInterface()
{
}

UPawnInputMovementComponent::UPawnInputMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPawnInputMovementComponent::AddLocation_Implementation(FVector2D InValue)
{
	if (APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		if (Pawn->GetClass()->ImplementsInterface(UPawnLockStateInterface::StaticClass()))
		{
			if (!Cast<IPawnLockStateInterface>(GetOwner())->CanMove(GetOwner()->GetActorLocation()))
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
			if (!Cast<IPawnLockStateInterface>(GetOwner())->CanTurn(GetOwner()->GetActorRotation()))
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
		if (!Cast<IPawnLockStateInterface>(GetOwner())->CanMove(GetOwner()->GetActorLocation()))
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
		if (!Cast<IPawnLockStateInterface>(GetOwner())->CanTurn(GetOwner()->GetActorRotation()))
		{
			return;
		}
	}

	GetOwner()->SetActorRotation(InValue);
}

void UPawnInputMovementComponent::SetZoom_Implementation(float InValue)
{
}

FVector UPawnInputMovementComponent::GetLocation()
{
	return GetOwner()->GetActorLocation();
}

FRotator UPawnInputMovementComponent::GetRotation()
{
	return GetOwner()->GetActorRotation();
}

float UPawnInputMovementComponent::GetZoom()
{
	return -1.f;
}

float UPawnInputMovementComponent::GetMovementSpeedRate()
{
	return MovementSpeedRate;
}

float UPawnInputMovementComponent::GetRotationSpeedRate()
{
	return RotationSpeedRate;
}

float UPawnInputMovementComponent::GetZoomSpeedRate()
{
	return ZoomSpeedRate;
}
