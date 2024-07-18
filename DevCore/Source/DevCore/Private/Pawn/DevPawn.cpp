// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/DevPawn.h"

#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Manager/ManagerGlobal.h"
#include "Pawn/PawnManager.h"

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
	GetManager<UPawnManager>()->RegisterPawn(this);
}

void ADevPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetManager<UPawnManager>()->UnRegisterPawn(this);
	Super::EndPlay(EndPlayReason);
}

void ADevPawn::NativeOnCreate()
{
	IProcedureBaseInterface::NativeOnCreate();
	Execute_OnCreate(this);
}

void ADevPawn::NativeOnDestroy()
{
	IProcedureBaseInterface::NativeOnDestroy();
	Execute_OnDestroy(this);
}

void ADevPawn::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();
	Execute_OnRefresh(this);
}

void ADevPawn::AddLocation_Implementation(FVector2D InValue)
{
	if (CanMove())
	{
		AddMovementInput(UKismetMathLibrary::GetRightVector(GetActorRotation()), InValue.X);
		AddMovementInput(UKismetMathLibrary::GetForwardVector(GetActorRotation()), InValue.Y);
	}
}

void ADevPawn::AddRotation_Implementation(FVector2D InValue)
{
	if (CanTurn())
	{
		AddControllerYawInput(InValue.X);
		AddControllerPitchInput(InValue.Y);
	}
}

void ADevPawn::SetLocation_Implementation(const FVector InValue)
{
	if (CanMove())
	{
		SetActorLocation(InValue);
	}
}

void ADevPawn::SetRotation_Implementation(const FRotator InValue)
{
	if (CanTurn())
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
