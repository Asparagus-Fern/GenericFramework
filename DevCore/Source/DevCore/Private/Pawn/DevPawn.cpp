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
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComponent;

	CommonSpringArmComponent = CreateDefaultSubobject<UCommonSpringArmComponent>("SpringArm");
	CommonSpringArmComponent->SetupAttachment(SceneComponent);
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(CommonSpringArmComponent);

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

	CommonSpringArmComponent->SpringArmLimit = PawnLockingState.SpringArmLimit;
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
	const FVector TargetLocation = Execute_GetLocation(this) + (UKismetMathLibrary::GetRightVector(GetActorRotation()) * InValue.X) + (UKismetMathLibrary::GetForwardVector(GetActorRotation()) * InValue.Y);
	if (PawnLockingState.CanMove(TargetLocation))
	{
		const float Rate = ((FMath::Abs(FMath::Sin(UE_DOUBLE_PI / (180.0) * Execute_GetRotation(this).Pitch)) * CommonSpringArmComponent->TargetArmLength) * UE_TWO_PI);

		FloatingPawnMovement->MaxSpeed = Rate;
		FloatingPawnMovement->Acceleration = Rate * 0.5f;
		FloatingPawnMovement->Deceleration = Rate * 0.5f;

		const FVector2D Movement = InValue * Rate * UPawnManagerSetting::Get()->MovementSpeed;
		AddMovementInput(UKismetMathLibrary::GetRightVector(GetActorRotation()), Movement.X);
		AddMovementInput(UKismetMathLibrary::GetForwardVector(GetActorRotation()), Movement.Y);
	}
}

void ADevPawn::AddRotation_Implementation(const FVector2D InValue)
{
	const FRotator TargetRotation = Execute_GetRotation(this) + FRotator(InValue.Y, InValue.X, 0.f);
	if (PawnLockingState.CanTurn(TargetRotation))
	{
		AddActorWorldRotation(FRotator(0.f, InValue.X, 0.f));
		CommonSpringArmComponent->AddRelativeRotation(FRotator(InValue.Y, 0.f, 0.f));
	}
}

void ADevPawn::SetLocation_Implementation(const FVector InValue)
{
	if (PawnLockingState.CanMove(InValue))
	{
		SetActorLocation(InValue);
	}
}

void ADevPawn::SetRotation_Implementation(const FRotator InValue)
{
	if (PawnLockingState.CanTurn(InValue))
	{
		SetActorRotation(FRotator(0.f, InValue.Yaw, 0.f));
		CommonSpringArmComponent->SetRelativeRotation(FRotator(InValue.Pitch, 0.f, 0.f), true);
	}
}

FVector ADevPawn::GetLocation_Implementation()
{
	return GetActorLocation();
}

FRotator ADevPawn::GetRotation_Implementation()
{
	return FRotator(CommonSpringArmComponent->GetRelativeRotation().Pitch, GetActorRotation().Yaw, 0.f);
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

void ADevPawn::SetPawnLockingState(FPawnLockingState InPawnLockingState)
{
	PawnLockingState = InPawnLockingState;
	CommonSpringArmComponent->SpringArmLimit = PawnLockingState.SpringArmLimit;
}

UCameraComponent* ADevPawn::GetActiveCameraComponent_Implementation()
{
	return CameraComponent;
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
		if (PawnLockingState.CanZoom(CommonSpringArmComponent->TargetArmLength + Value))
		{
			CommonSpringArmComponent->AddTargetArmLength(Value);
		}
	}
}

void ADevPawn::OnZoomEnd_Implementation(const FInputActionValue& InValue)
{
}
