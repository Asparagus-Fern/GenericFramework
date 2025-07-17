// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Character/GenericCharacter.h"

#include "AIController.h"
#include "Kismet/KismetMathLibrary.h"

AGenericCharacter::FCharacterDelegate AGenericCharacter::OnCharacterRegister;
AGenericCharacter::FCharacterDelegate AGenericCharacter::OnCharacterUnRegister;

AGenericCharacter::AGenericCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterName = "DevCharacter";

	InputMovementComponent = CreateDefaultSubobject<UPawnInputMovementComponent>("InputMovementComponent");
	LockStateComponent = CreateDefaultSubobject<UPawnLockStateComponent>("LockStateComponent");
}

void AGenericCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnCharacterRegister.Broadcast(this);
}

void AGenericCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnCharacterUnRegister.Broadcast(this);
	Super::EndPlay(EndPlayReason);
}

void AGenericCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInput)
{
	Super::SetupPlayerInputComponent(PlayerInput);
}

FPawnLockState AGenericCharacter::GetPawnLockState()
{
	return LockStateComponent->GetPawnLockState();
}

bool AGenericCharacter::CanMove(const FVector& TargetLocation) const
{
	return LockStateComponent->CanMove(TargetLocation);
}

bool AGenericCharacter::CanTurn(const FRotator& TargetRotation) const
{
	return LockStateComponent->CanTurn(TargetRotation);
}

bool AGenericCharacter::CanZoom(float TargetSpringArmLength) const
{
	return LockStateComponent->CanZoom(TargetSpringArmLength);
}

FVector AGenericCharacter::GetLimitLocation(const FVector& TargetLocation) const
{
	return LockStateComponent->GetLimitLocation(TargetLocation);
}

FRotator AGenericCharacter::GetLimitRotation(const FRotator& TargetRotation) const
{
	return LockStateComponent->GetLimitRotation(TargetRotation);
}

float AGenericCharacter::GetLimitSpringArmLength(float TargetSpringArmLength) const
{
	return LockStateComponent->GetLimitSpringArmLength(TargetSpringArmLength);
}

void AGenericCharacter::SetPawnLockState_Implementation(const FPawnLockState& InPawnLockState)
{
	IPawnLockStateInterface::Execute_SetPawnLockState(LockStateComponent, InPawnLockState);
}

void AGenericCharacter::SetIsFullyLock_Implementation(bool InFullyLock)
{
	IPawnLockStateInterface::Execute_SetIsFullyLock(LockStateComponent, InFullyLock);
}

void AGenericCharacter::SetIsLockLocation_Implementation(bool InLockLocation)
{
	IPawnLockStateInterface::Execute_SetIsLockLocation(LockStateComponent, InLockLocation);
}

void AGenericCharacter::SetIsLockRotation_Implementation(bool InLockRotation)
{
	IPawnLockStateInterface::Execute_SetIsLockRotation(LockStateComponent, InLockRotation);
}

void AGenericCharacter::SetIsLockSpringArm_Implementation(bool InLockSpringArm)
{
	IPawnLockStateInterface::Execute_SetIsLockSpringArm(LockStateComponent, InLockSpringArm);
}
