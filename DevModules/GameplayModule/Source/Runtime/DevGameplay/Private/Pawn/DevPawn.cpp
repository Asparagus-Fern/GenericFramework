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

bool ADevPawn::IsPlayer()
{
	return IsValid(Cast<APlayerController>(GetController()));
}

bool ADevPawn::IsAI()
{
	return IsValid(Cast<AAIController>(GetController()));
}

APlayerController* ADevPawn::GetPlayerController()
{
	return Cast<APlayerController>(GetController());
}

AAIController* ADevPawn::GetAIController()
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

FVector ADevPawn::GetLocation()
{
	return InputMovementComponent->GetLocation();
}

FRotator ADevPawn::GetRotation()
{
	return InputMovementComponent->GetRotation();
}

float ADevPawn::GetZoom()
{
	return InputMovementComponent->GetZoom();
}

float ADevPawn::GetMovementSpeedRate()
{
	return InputMovementComponent->GetMovementSpeedRate();
}

float ADevPawn::GetRotationSpeedRate()
{
	return InputMovementComponent->GetRotationSpeedRate();
}

float ADevPawn::GetZoomSpeedRate()
{
	return InputMovementComponent->GetZoomSpeedRate();
}

FPawnLockState ADevPawn::GetPawnLockState()
{
	return LockStateComponent->GetPawnLockState();
}

bool ADevPawn::CanMove(const FVector& TargetLocation) const
{
	return LockStateComponent->CanMove(TargetLocation);
}

bool ADevPawn::CanTurn(const FRotator& TargetRotation) const
{
	return LockStateComponent->CanTurn(TargetRotation);
}

bool ADevPawn::CanZoom(float TargetSpringArmLength) const
{
	return LockStateComponent->CanZoom(TargetSpringArmLength);
}

FVector ADevPawn::GetLimitLocation(const FVector& TargetLocation) const
{
	return LockStateComponent->GetLimitLocation(TargetLocation);
}

FRotator ADevPawn::GetLimitRotation(const FRotator& TargetRotation) const
{
	return LockStateComponent->GetLimitRotation(TargetRotation);
}

float ADevPawn::GetLimitSpringArmLength(float TargetSpringArmLength) const
{
	return LockStateComponent->GetLimitSpringArmLength(TargetSpringArmLength);
}

void ADevPawn::SetPawnLockState_Implementation(const FPawnLockState& InPawnLockState)
{
	IPawnLockStateInterface::Execute_SetPawnLockState(LockStateComponent, InPawnLockState);
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
