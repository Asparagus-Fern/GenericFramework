// Copyright ChenTaiye 2025. All Rights Reserved.


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

FPawnLockState ADevCharacter::GetPawnLockState()
{
	return LockStateComponent->GetPawnLockState();
}

bool ADevCharacter::CanMove(const FVector& TargetLocation) const
{
	return LockStateComponent->CanMove(TargetLocation);
}

bool ADevCharacter::CanTurn(const FRotator& TargetRotation) const
{
	return LockStateComponent->CanTurn(TargetRotation);
}

bool ADevCharacter::CanZoom(float TargetSpringArmLength) const
{
	return LockStateComponent->CanZoom(TargetSpringArmLength);
}

FVector ADevCharacter::GetLimitLocation(const FVector& TargetLocation) const
{
	return LockStateComponent->GetLimitLocation(TargetLocation);
}

FRotator ADevCharacter::GetLimitRotation(const FRotator& TargetRotation) const
{
	return LockStateComponent->GetLimitRotation(TargetRotation);
}

float ADevCharacter::GetLimitSpringArmLength(float TargetSpringArmLength) const
{
	return LockStateComponent->GetLimitSpringArmLength(TargetSpringArmLength);
}

void ADevCharacter::SetPawnLockState_Implementation(const FPawnLockState& InPawnLockState)
{
	IPawnLockStateInterface::Execute_SetPawnLockState(LockStateComponent, InPawnLockState);
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
