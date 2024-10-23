// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/DevPawn.h"

#include "AIController.h"
#include "Camera/CameraComponent.h"
#include "Input/PlayerInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pawn/PawnManagerSetting.h"

ADevPawn::FPawnDelegate ADevPawn::OnPawnRegister;
ADevPawn::FPawnDelegate ADevPawn::OnPawnUnRegister;

ADevPawn::ADevPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	PawnName = "DevPawn";
	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComponent;

	PlayerInputComponent = CreateDefaultSubobject<UPlayerInputComponent>("PlayerInputComponent");
}

void ADevPawn::BeginPlay()
{
	Super::BeginPlay();

	OnPawnRegister.Broadcast(this);
}

void ADevPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (IsValid(Execute_GetPlayerInputComponent(this)))
	{
		Execute_GetPlayerInputComponent(this)->RemovePlayerInput(InputComponent);
	}

	OnPawnUnRegister.Broadcast(this);

	Super::EndPlay(EndPlayReason);
}

void ADevPawn::SetupPlayerInputComponent(UInputComponent* PlayerInput)
{
	Super::SetupPlayerInputComponent(PlayerInput);

	if (IsValid(Execute_GetPlayerInputComponent(this)))
	{
		Execute_GetPlayerInputComponent(this)->SetupPlayerInput(PlayerInput);
	}
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

void ADevPawn::AddZoom_Implementation(float InValue)
{
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

void ADevPawn::SetZoom_Implementation(float InValue)
{
}

FVector ADevPawn::GetLocation_Implementation()
{
	return GetActorLocation();
}

FRotator ADevPawn::GetRotation_Implementation()
{
	return GetActorRotation();
}

float ADevPawn::GetZoom_Implementation()
{
	return -1.f;
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

UPlayerInputComponent* ADevPawn::GetPlayerInputComponent_Implementation()
{
	return IsValid(PlayerInputComponent) ? PlayerInputComponent : nullptr;
}

UCameraComponent* ADevPawn::GetActiveCameraComponent_Implementation()
{
	return nullptr;
}

void ADevPawn::SetPawnLockingState_Implementation(FPawnLockingState InPawnLockingState)
{
	PawnLockingState = InPawnLockingState;
}
