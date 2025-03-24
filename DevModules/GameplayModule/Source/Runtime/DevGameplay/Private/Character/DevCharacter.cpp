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

bool ADevCharacter::IsPlayer()
{
	return IsValid(Cast<APlayerController>(GetController()));
}

bool ADevCharacter::IsAI()
{
	return IsValid(Cast<AAIController>(GetController()));
}

APlayerController* ADevCharacter::GetPlayerController()
{
	return Cast<APlayerController>(GetController());
}

AAIController* ADevCharacter::GetAIController()
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

FVector ADevCharacter::GetLocation()
{
	return InputMovementComponent->GetLocation();
}

FRotator ADevCharacter::GetRotation()
{
	return InputMovementComponent->GetRotation();
}

float ADevCharacter::GetZoom()
{
	return InputMovementComponent->GetZoom();
}

float ADevCharacter::GetZoomSpeedRate()
{
	return InputMovementComponent->GetZoomSpeedRate();
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
