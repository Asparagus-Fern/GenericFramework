// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DevCharacter.h"

#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

ADevCharacter::FCharacterDelegate ADevCharacter::OnCharacterRegister;
ADevCharacter::FCharacterDelegate ADevCharacter::OnCharacterUnRegister;

ADevCharacter::ADevCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterName = "DevCharacter";

	InputMovementComponent = CreateDefaultSubobject<UPawnInputMovementComponent>("InputMovementComponent");
	LockStateComponent = CreateDefaultSubobject<UPawnLockStateComponent>("LockStateComponent");
}

void ADevCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnCharacterRegister.Broadcast(this);
}

void ADevCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnCharacterUnRegister.Broadcast(this);
	Super::EndPlay(EndPlayReason);
}

void ADevCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInput)
{
	Super::SetupPlayerInputComponent(PlayerInput);
}

bool ADevCharacter::IsPlayer_Implementation()
{
	return IsValid(Cast<APlayerController>(GetController()));
}

bool ADevCharacter::IsAI_Implementation()
{
	return IsValid(Cast<AAIController>(GetController()));
}

APlayerController* ADevCharacter::GetPlayerController_Implementation()
{
	return Cast<APlayerController>(GetController());
}

AAIController* ADevCharacter::GetAIController_Implementation()
{
	return Cast<AAIController>(GetController());
}

void ADevCharacter::AddLocation_Implementation(FVector2D InValue)
{
	IPawnInputMovementInterface::Execute_AddLocation(InputMovementComponent, InValue);
}

void ADevCharacter::AddRotation_Implementation(FVector2D InValue)
{
	IPawnInputMovementInterface::Execute_AddRotation(InputMovementComponent, InValue);
}

void ADevCharacter::AddZoom_Implementation(float InValue)
{
	IPawnInputMovementInterface::Execute_AddZoom(InputMovementComponent, InValue);
}

void ADevCharacter::SetLocation_Implementation(FVector InValue)
{
	IPawnInputMovementInterface::Execute_SetLocation(InputMovementComponent, InValue);
}

void ADevCharacter::SetRotation_Implementation(FRotator InValue)
{
	IPawnInputMovementInterface::Execute_SetRotation(InputMovementComponent, InValue);
}

void ADevCharacter::SetZoom_Implementation(float InValue)
{
	IPawnInputMovementInterface::Execute_SetZoom(InputMovementComponent, InValue);
}

FVector ADevCharacter::GetLocation_Implementation()
{
	return IPawnInputMovementInterface::Execute_GetLocation(InputMovementComponent);
}

FRotator ADevCharacter::GetRotation_Implementation()
{
	return IPawnInputMovementInterface::Execute_GetRotation(InputMovementComponent);
}

float ADevCharacter::GetZoom_Implementation()
{
	return IPawnInputMovementInterface::Execute_GetZoom(InputMovementComponent);
}

float ADevCharacter::GetZoomSpeedRate_Implementation()
{
	return IPawnInputMovementInterface::Execute_GetZoomSpeedRate(InputMovementComponent);
}

FPawnLockState ADevCharacter::GetPawnLockState_Implementation()
{
	return IPawnLockStateInterface::Execute_GetPawnLockState(LockStateComponent);
}


void ADevCharacter::SetPawnLockState_Implementation(const FPawnLockState& InPawnLockState)
{
	IPawnLockStateInterface::Execute_SetPawnLockState(LockStateComponent, InPawnLockState);
}

bool ADevCharacter::CanMove_Implementation(const FVector& TargetLocation) const
{
	return IPawnLockStateInterface::Execute_CanMove(LockStateComponent, TargetLocation);
}

bool ADevCharacter::CanTurn_Implementation(const FRotator& TargetRotation) const
{
	return IPawnLockStateInterface::Execute_CanTurn(LockStateComponent, TargetRotation);
}

bool ADevCharacter::CanZoom_Implementation(float TargetSpringArmLength) const
{
	return IPawnLockStateInterface::Execute_CanZoom(LockStateComponent, TargetSpringArmLength);
}

void ADevCharacter::SetIsFullyLock_Implementation(bool InFullyLock)
{
	IPawnLockStateInterface::Execute_SetIsFullyLock(LockStateComponent, InFullyLock);
}

void ADevCharacter::SetIsLockLocation_Implementation(bool InLockLocation)
{
	IPawnLockStateInterface::Execute_SetIsLockLocation(LockStateComponent, InLockLocation);
}

void ADevCharacter::SetIsLockRotation_Implementation(bool InLockRotation)
{
	IPawnLockStateInterface::Execute_SetIsLockRotation(LockStateComponent, InLockRotation);
}

void ADevCharacter::SetIsLockSpringArm_Implementation(bool InLockSpringArm)
{
	IPawnLockStateInterface::Execute_SetIsLockSpringArm(LockStateComponent, InLockSpringArm);
}

FVector ADevCharacter::GetLimitLocation_Implementation(const FVector& TargetLocation) const
{
	return IPawnLockStateInterface::Execute_GetLimitLocation(LockStateComponent, TargetLocation);
}

FRotator ADevCharacter::GetLimitRotation_Implementation(const FRotator& TargetRotation) const
{
	return IPawnLockStateInterface::Execute_GetLimitRotation(LockStateComponent, TargetRotation);
}

float ADevCharacter::GetLimitSpringArmLength_Implementation(float TargetSpringArmLength) const
{
	return IPawnLockStateInterface::Execute_GetLimitSpringArmLength(LockStateComponent, TargetSpringArmLength);
}
