// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/DevPawn.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Manager/ManagerGlobal.h"
#include "Pawn/PawnManager.h"
#include "Pawn/PawnManagerSetting.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Pawn, "Pawn");

ADevPawn::ADevPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;
	bUseControllerRotationYaw = true;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
}

void ADevPawn::BeginPlay()
{
	Super::BeginPlay();

	if (UPawnManager* PawnManager = GetManager<UPawnManager>(this))
	{
		PawnManager->RegisterPawn(this);
	}
}

void ADevPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UPawnManager* PawnManager = GetManager<UPawnManager>(this))
	{
		PawnManager->UnRegisterPawn(this);
	}

	Super::EndPlay(EndPlayReason);
}

void ADevPawn::AddLocation_Implementation(const FVector2D InValue)
{
	if (PawnLockingState.CanMove(GetActorLocation()))
	{
		const FVector2D Movement = InValue * UPawnManagerSetting::Get()->MovementSpeed;

		AddMovementInput(UKismetMathLibrary::GetRightVector(GetActorRotation()), Movement.X);
		AddMovementInput(UKismetMathLibrary::GetForwardVector(GetActorRotation()), Movement.Y);
	}
}

void ADevPawn::AddRotation_Implementation(const FVector2D InValue)
{
	if (PawnLockingState.CanTurn(GetActorRotation()))
	{
		const FVector2D Rotation = InValue * UPawnManagerSetting::Get()->RotationSpeed;

		AddControllerYawInput(Rotation.X);
		AddControllerPitchInput(Rotation.Y);
	}
}

void ADevPawn::SetLocation_Implementation(const FVector InValue)
{
	if (PawnLockingState.CanMove(GetActorLocation()))
	{
		SetActorLocation(InValue);
	}
}

void ADevPawn::SetRotation_Implementation(const FRotator InValue)
{
	if (PawnLockingState.CanTurn(GetActorRotation()))
	{
		SetActorRotation(InValue);
	}
}

FVector ADevPawn::GetLocation_Implementation()
{
	return GetActorLocation();
}

FRotator ADevPawn::GetRotation_Implementation()
{
	return GetActorRotation();
}

FVector ADevPawn::GetCameraLocation_Implementation()
{
	return GetPlayerController()->PlayerCameraManager->GetCameraLocation();
}

FRotator ADevPawn::GetCameraRotation_Implementation()
{
	return GetPlayerController()->PlayerCameraManager->GetCameraRotation();
}

APawn* ADevPawn::GetPawn()
{
	return this;
}

FGameplayTag ADevPawn::GetPawnTag()
{
	return PawnTag;
}

APlayerController* ADevPawn::GetPlayerController() const
{
	return Cast<APlayerController>(GetController());
}
