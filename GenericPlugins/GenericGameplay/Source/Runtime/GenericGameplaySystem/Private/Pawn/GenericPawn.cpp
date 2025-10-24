// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Pawn/GenericPawn.h"

#include "Component/PawnInputMovementComponent.h"
#include "Component/PawnLockStateComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

AGenericPawn::AGenericPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComponent;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComponent");
	LockStateComponent = CreateDefaultSubobject<UPawnLockStateComponent>("LockStateComponent");
	InputMovementComponent = CreateDefaultSubobject<UPawnInputMovementComponent>("InputMovementComponent");
}

void AGenericPawn::AddLocation_Implementation(const FVector2D InValue)
{
	IPawnInputMovementInterface::Execute_AddLocation(InputMovementComponent, InValue);
}

void AGenericPawn::AddRotation_Implementation(const FVector2D InValue)
{
	IPawnInputMovementInterface::Execute_AddRotation(InputMovementComponent, InValue);
}

void AGenericPawn::AddZoom_Implementation(float InValue)
{
	IPawnInputMovementInterface::Execute_AddZoom(InputMovementComponent, InValue);
}

void AGenericPawn::SetLocation_Implementation(const FVector InValue)
{
	IPawnInputMovementInterface::Execute_SetLocation(InputMovementComponent, InValue);
}

void AGenericPawn::SetRotation_Implementation(const FRotator InValue)
{
	IPawnInputMovementInterface::Execute_SetRotation(InputMovementComponent, InValue);
}

void AGenericPawn::SetZoom_Implementation(float InValue)
{
	IPawnInputMovementInterface::Execute_SetZoom(InputMovementComponent, InValue);
}

FVector AGenericPawn::GetLocation()
{
	return InputMovementComponent->GetLocation();
}

FRotator AGenericPawn::GetRotation()
{
	return InputMovementComponent->GetRotation();
}

float AGenericPawn::GetZoom()
{
	return InputMovementComponent->GetZoom();
}

float AGenericPawn::GetMovementSpeedRate()
{
	return InputMovementComponent->GetMovementSpeedRate();
}

float AGenericPawn::GetRotationSpeedRate()
{
	return InputMovementComponent->GetRotationSpeedRate();
}

float AGenericPawn::GetZoomSpeedRate()
{
	return InputMovementComponent->GetZoomSpeedRate();
}

FPawnLockState AGenericPawn::GetPawnLockState()
{
	return LockStateComponent->GetPawnLockState();
}

bool AGenericPawn::CanMove(const FVector& TargetLocation) const
{
	return LockStateComponent->CanMove(TargetLocation);
}

bool AGenericPawn::CanTurn(const FRotator& TargetRotation) const
{
	return LockStateComponent->CanTurn(TargetRotation);
}

bool AGenericPawn::CanZoom(float TargetSpringArmLength) const
{
	return LockStateComponent->CanZoom(TargetSpringArmLength);
}

FVector AGenericPawn::GetLimitLocation(const FVector& TargetLocation) const
{
	return LockStateComponent->GetLimitLocation(TargetLocation);
}

FRotator AGenericPawn::GetLimitRotation(const FRotator& TargetRotation) const
{
	return LockStateComponent->GetLimitRotation(TargetRotation);
}

float AGenericPawn::GetLimitSpringArmLength(float TargetSpringArmLength) const
{
	return LockStateComponent->GetLimitSpringArmLength(TargetSpringArmLength);
}

void AGenericPawn::SetPawnLockState_Implementation(const FPawnLockState& InPawnLockState)
{
	IPawnLockStateInterface::Execute_SetPawnLockState(LockStateComponent, InPawnLockState);
}

void AGenericPawn::SetIsFullyLock_Implementation(bool InFullyLock)
{
	IPawnLockStateInterface::Execute_SetIsFullyLock(LockStateComponent, InFullyLock);
}

void AGenericPawn::SetIsLockLocation_Implementation(bool InLockLocation)
{
	IPawnLockStateInterface::Execute_SetIsLockLocation(LockStateComponent, InLockLocation);
}

void AGenericPawn::SetIsLockRotation_Implementation(bool InLockRotation)
{
	IPawnLockStateInterface::Execute_SetIsLockRotation(LockStateComponent, InLockRotation);
}

void AGenericPawn::SetIsLockSpringArm_Implementation(bool InLockSpringArm)
{
	IPawnLockStateInterface::Execute_SetIsLockSpringArm(LockStateComponent, InLockSpringArm);
}
