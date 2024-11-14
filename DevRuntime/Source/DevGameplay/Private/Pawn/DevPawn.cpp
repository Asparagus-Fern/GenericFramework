// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/DevPawn.h"

#include "AIController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

ADevPawn::FPawnDelegate ADevPawn::OnPawnRegister;
ADevPawn::FPawnDelegate ADevPawn::OnPawnUnRegister;

IPawnInterface::IPawnInterface()
{
}

ADevPawn::ADevPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	PawnName = "DevPawn";
	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComponent;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("MovementComponent");
	LockStateComponent = CreateDefaultSubobject<UPawnLockStateComponent>("LockStateComponent");
	InputMovementComponent = CreateDefaultSubobject<UPawnInputMovementComponent>("InputMovementComponent");
}

void ADevPawn::BeginPlay()
{
	Super::BeginPlay();
	OnPawnRegister.Broadcast(this);
}

void ADevPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnPawnUnRegister.Broadcast(this);
	Super::EndPlay(EndPlayReason);
}

bool ADevPawn::IsPlayer_Implementation()
{
	return IsValid(Cast<APlayerController>(GetController()));
}

bool ADevPawn::IsAI_Implementation()
{
	return IsValid(Cast<AAIController>(GetController()));
}

APlayerController* ADevPawn::GetPlayerController_Implementation()
{
	return Cast<APlayerController>(GetController());
}

AAIController* ADevPawn::GetAIController_Implementation()
{
	return Cast<AAIController>(GetController());
}

void ADevPawn::AddLocation_Implementation(const FVector2D InValue)
{
	IPawnInputMovementInterface::Execute_AddLocation(InputMovementComponent, InValue);
}

void ADevPawn::AddRotation_Implementation(const FVector2D InValue)
{
	IPawnInputMovementInterface::Execute_AddRotation(InputMovementComponent, InValue);
}

void ADevPawn::AddZoom_Implementation(float InValue)
{
	IPawnInputMovementInterface::Execute_AddZoom(InputMovementComponent, InValue);
}

void ADevPawn::SetLocation_Implementation(const FVector InValue)
{
	IPawnInputMovementInterface::Execute_SetLocation(InputMovementComponent, InValue);
}

void ADevPawn::SetRotation_Implementation(const FRotator InValue)
{
	IPawnInputMovementInterface::Execute_SetRotation(InputMovementComponent, InValue);
}

void ADevPawn::SetZoom_Implementation(float InValue)
{
	IPawnInputMovementInterface::Execute_SetZoom(InputMovementComponent, InValue);
}

FVector ADevPawn::GetLocation_Implementation()
{
	return IPawnInputMovementInterface::Execute_GetLocation(InputMovementComponent);
}

FRotator ADevPawn::GetRotation_Implementation()
{
	return IPawnInputMovementInterface::Execute_GetRotation(InputMovementComponent);
}

float ADevPawn::GetZoom_Implementation()
{
	return IPawnInputMovementInterface::Execute_GetZoom(InputMovementComponent);
}

float ADevPawn::GetMovementSpeedRate_Implementation()
{
	return IPawnInputMovementInterface::Execute_GetMovementSpeedRate(InputMovementComponent);
}

float ADevPawn::GetRotationSpeedRate_Implementation()
{
	return IPawnInputMovementInterface::Execute_GetRotationSpeedRate(InputMovementComponent);
}

float ADevPawn::GetZoomSpeedRate_Implementation()
{
	return IPawnInputMovementInterface::Execute_GetZoomSpeedRate(InputMovementComponent);
}

FPawnLockState ADevPawn::GetPawnLockState_Implementation()
{
	return IPawnLockStateInterface::Execute_GetPawnLockState(LockStateComponent);
}

void ADevPawn::SetPawnLockState_Implementation(const FPawnLockState& InPawnLockState)
{
	IPawnLockStateInterface::Execute_SetPawnLockState(LockStateComponent, InPawnLockState);
}

bool ADevPawn::CanMove_Implementation(const FVector& TargetLocation) const
{
	return IPawnLockStateInterface::Execute_CanMove(LockStateComponent, TargetLocation);
}

bool ADevPawn::CanTurn_Implementation(const FRotator& TargetRotation) const
{
	return IPawnLockStateInterface::Execute_CanTurn(LockStateComponent, TargetRotation);
}

bool ADevPawn::CanZoom_Implementation(float TargetSpringArmLength) const
{
	return IPawnLockStateInterface::Execute_CanZoom(LockStateComponent, TargetSpringArmLength);
}

void ADevPawn::SetIsFullyLock_Implementation(bool InFullyLock)
{
	IPawnLockStateInterface::Execute_SetIsFullyLock(LockStateComponent, InFullyLock);
}

void ADevPawn::SetIsLockLocation_Implementation(bool InLockLocation)
{
	IPawnLockStateInterface::Execute_SetIsLockLocation(LockStateComponent, InLockLocation);
}

void ADevPawn::SetIsLockRotation_Implementation(bool InLockRotation)
{
	IPawnLockStateInterface::Execute_SetIsLockRotation(LockStateComponent, InLockRotation);
}

void ADevPawn::SetIsLockSpringArm_Implementation(bool InLockSpringArm)
{
	IPawnLockStateInterface::Execute_SetIsLockSpringArm(LockStateComponent, InLockSpringArm);
}

FVector ADevPawn::GetLimitLocation_Implementation(const FVector& TargetLocation) const
{
	return IPawnLockStateInterface::Execute_GetLimitLocation(LockStateComponent, TargetLocation);
}

FRotator ADevPawn::GetLimitRotation_Implementation(const FRotator& TargetRotation) const
{
	return IPawnLockStateInterface::Execute_GetLimitRotation(LockStateComponent, TargetRotation);
}

float ADevPawn::GetLimitSpringArmLength_Implementation(float TargetSpringArmLength) const
{
	return IPawnLockStateInterface::Execute_GetLimitSpringArmLength(LockStateComponent, TargetSpringArmLength);
}
