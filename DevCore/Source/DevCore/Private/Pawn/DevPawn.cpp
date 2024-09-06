// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/DevPawn.h"

#include "AIController.h"
#include "EnhancedInputComponent.h"
#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Camera/CameraComponent.h"
#include "Component/CommonSpringArmComponent.h"
#include "Debug/DebugType.h"
#include "GameFramework/FloatingPawnMovement.h"
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

	const ConstructorHelpers::FObjectFinder<UInputAction> MoveAction(TEXT("/Script/EnhancedInput.InputAction'/DevCore/Input/MovementActions/IA_Move.IA_Move'"));
	const ConstructorHelpers::FObjectFinder<UInputAction> TurnAction(TEXT("/Script/EnhancedInput.InputAction'/DevCore/Input/MovementActions/IA_Turn.IA_Turn'"));
	const ConstructorHelpers::FObjectFinder<UInputAction> ZoomAction(TEXT("/Script/EnhancedInput.InputAction'/DevCore/Input/MovementActions/IA_Zoom.IA_Zoom'"));

	IA_Move = MoveAction.Object;
	IA_Turn = TurnAction.Object;
	IA_Zoom = ZoomAction.Object;
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

void ADevPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Move)
		{
			EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Started, this, &ADevPawn::OnMoveStart);
			EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ADevPawn::OnMoving);
			EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Completed, this, &ADevPawn::OnMoveEnd);
		}

		if (IA_Turn)
		{
			EnhancedInputComponent->BindAction(IA_Turn, ETriggerEvent::Started, this, &ADevPawn::OnTurnStart);
			EnhancedInputComponent->BindAction(IA_Turn, ETriggerEvent::Triggered, this, &ADevPawn::OnTurning);
			EnhancedInputComponent->BindAction(IA_Turn, ETriggerEvent::Completed, this, &ADevPawn::OnTurnEnd);
		}

		if (IA_Zoom)
		{
			EnhancedInputComponent->BindAction(IA_Zoom, ETriggerEvent::Started, this, &ADevPawn::OnZoomStart);
			EnhancedInputComponent->BindAction(IA_Zoom, ETriggerEvent::Triggered, this, &ADevPawn::OnZooming);
			EnhancedInputComponent->BindAction(IA_Zoom, ETriggerEvent::Completed, this, &ADevPawn::OnZoomEnd);
		}
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

void ADevPawn::SetPawnLockingState_Implementation(FPawnLockingState InPawnLockingState)
{
	PawnLockingState = InPawnLockingState;
}

UCameraComponent* ADevPawn::GetActiveCameraComponent_Implementation()
{
	return nullptr;
}

void ADevPawn::OnMoveStart_Implementation(const FInputActionValue& InValue)
{
}

void ADevPawn::OnMoving_Implementation(const FInputActionValue& InValue)
{
	if (InValue.GetMagnitude() != 0.f)
	{
		const FVector2D Value = InValue.Get<FInputActionValue::Axis2D>();
		Execute_AddLocation(this, Value);
	}
}

void ADevPawn::OnMoveEnd_Implementation(const FInputActionValue& InValue)
{
}

void ADevPawn::OnTurnStart_Implementation(const FInputActionValue& InValue)
{
}

void ADevPawn::OnTurning_Implementation(const FInputActionValue& InValue)
{
	if (InValue.GetMagnitude() != 0.f)
	{
		const FVector2D Value = InValue.Get<FInputActionValue::Axis2D>();
		Execute_AddRotation(this, Value);
	}
}

void ADevPawn::OnTurnEnd_Implementation(const FInputActionValue& InValue)
{
}

void ADevPawn::OnZoomStart_Implementation(const FInputActionValue& InValue)
{
}

void ADevPawn::OnZooming_Implementation(const FInputActionValue& InValue)
{
	if (InValue.GetMagnitude() != 0.f)
	{
		const float Value = InValue.Get<FInputActionValue::Axis1D>();
		Execute_AddZoom(this, Value);
	}
}

void ADevPawn::OnZoomEnd_Implementation(const FInputActionValue& InValue)
{
}
