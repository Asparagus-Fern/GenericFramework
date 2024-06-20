// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/DevPawn.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"

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
}

void ADevPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADevPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADevPawn::AddLocation_Implementation(FVector2D InValue)
{
	AddMovementInput(UKismetMathLibrary::GetRightVector(GetActorRotation()), InValue.X);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(GetActorRotation()), InValue.Y);
}

void ADevPawn::AddRotation_Implementation(FVector2D InValue)
{
	AddControllerYawInput(InValue.X);
	AddControllerPitchInput(InValue.Y);
}

FVector ADevPawn::GetLocation_Implementation()
{
	return GetActorLocation();
}

FRotator ADevPawn::GetRotation_Implementation()
{
	return GetActorRotation();
}

void ADevPawn::SetLocation_Implementation(const FVector InValue)
{
	SetActorLocation(InValue);
}

void ADevPawn::SetRotation_Implementation(const FRotator InValue)
{
	SetActorRotation(InValue);
}

APlayerController* ADevPawn::GetPlayerController() const
{
	return Cast<APlayerController>(GetController());
}
