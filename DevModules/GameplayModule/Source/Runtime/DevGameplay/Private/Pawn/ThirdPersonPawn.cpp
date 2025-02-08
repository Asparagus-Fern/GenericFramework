// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/ThirdPersonPawn.h"

#include "Camera/CameraComponent.h"
#include "CameraHandle/CameraHandle.h"
#include "CameraPoint/CameraPointBase.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pawn/Component/PawnSpringArmComponent.h"


AThirdPersonPawn::AThirdPersonPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PawnName = "ThirdPersonPawn";

	SpringArmComponent = CreateDefaultSubobject<UPawnSpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AThirdPersonPawn::BeginPlay()
{
	Super::BeginPlay();

	UCameraHandle::OnSwitchCameraBegin.AddUObject(this, &AThirdPersonPawn::OnSwitchCameraBegin);
	UCameraHandle::OnSwitchCameraFinish.AddUObject(this, &AThirdPersonPawn::OnSwitchCameraFinish);
}

void AThirdPersonPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UCameraHandle::OnSwitchCameraBegin.RemoveAll(this);
	UCameraHandle::OnSwitchCameraFinish.RemoveAll(this);

	Super::EndPlay(EndPlayReason);
}

void AThirdPersonPawn::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
{
	if (IsValid(GetActiveCameraComponent_Implementation()))
	{
		GetActiveCameraComponent_Implementation()->GetCameraView(DeltaTime, OutResult);
	}
	else
	{
		Super::CalcCamera(DeltaTime, OutResult);
	}
}

void AThirdPersonPawn::AddLocation_Implementation(FVector2D InValue)
{
	const FVector TargetLocation = Execute_GetLocation(this) + (UKismetMathLibrary::GetRightVector(GetActorRotation()) * InValue.X) + (UKismetMathLibrary::GetForwardVector(GetActorRotation()) * InValue.Y);
	if (Execute_CanMove(this, TargetLocation))
	{
		const float PitchRate = FMath::Pow(2, FMath::Sin(UE_DOUBLE_PI / (180.0) * FMath::Abs(Execute_GetRotation(this).Pitch)));
		const float MovementRate = FMath::Pow(2, IPawnInputMovementInterface::Execute_GetMovementSpeedRate(this));

		FloatingPawnMovement->MaxSpeed = PitchRate * MovementRate * UE_PI;
		FloatingPawnMovement->Acceleration = PitchRate * MovementRate * UE_HALF_PI;
		FloatingPawnMovement->Deceleration = PitchRate * MovementRate * UE_HALF_PI;

		const float Height = FMath::Sin(UE_DOUBLE_PI / (180.0) * FMath::Abs(Execute_GetRotation(this).Pitch)) * SpringArmComponent->TargetArmLength;
		if (Height > 0)
		{
			FloatingPawnMovement->MaxSpeed *= Height;
			FloatingPawnMovement->Acceleration *= Height;
			FloatingPawnMovement->Deceleration *= Height;
		}

		// DLOG(DLogDefault, Warning, TEXT("PitchRate : %f"), PitchRate)
		// DLOG(DLogDefault, Warning, TEXT("Height : %f"), Height)
		// DLOG(DLogDefault, Warning, TEXT("MovementRate : %f"), MovementRate)
		//
		// DLOG(DLogDefault, Warning, TEXT("MaxSpeed : %f"), FloatingPawnMovement->MaxSpeed)
		// DLOG(DLogDefault, Warning, TEXT("Acceleration : %f"), FloatingPawnMovement->Acceleration)
		// DLOG(DLogDefault, Warning, TEXT("Deceleration : %f"), FloatingPawnMovement->Deceleration)

		const FVector2D Movement = InValue * MovementRate;
		AddMovementInput(UKismetMathLibrary::GetRightVector(GetActorRotation()), Movement.X);
		AddMovementInput(UKismetMathLibrary::GetForwardVector(GetActorRotation()), Movement.Y);
	}
}

void AThirdPersonPawn::AddRotation_Implementation(FVector2D InValue)
{
	const float Pitch = InValue.Y * IPawnInputMovementInterface::Execute_GetRotationSpeedRate(this);
	const float Yaw = InValue.X * IPawnInputMovementInterface::Execute_GetRotationSpeedRate(this);
	const FRotator TargetRotation = Execute_GetRotation(this) + FRotator(Pitch, Yaw, 0.f);

	// DLOG(DLogDefault, Warning, TEXT("TargetRotation : %s"), *TargetRotation.ToString())

	if (Execute_CanTurn(this, TargetRotation))
	{
		AddActorWorldRotation(FRotator(0.f, Yaw, 0.f));
		SpringArmComponent->AddRelativeRotation(FRotator(Pitch, 0.f, 0.f));
	}
}

void AThirdPersonPawn::AddZoom_Implementation(float InValue)
{
	if (Execute_CanZoom(this, SpringArmComponent->TargetArmLength + InValue))
	{
		SpringArmComponent->AddTargetArmLength(InValue);
	}
}

void AThirdPersonPawn::SetLocation_Implementation(FVector InValue)
{
	if (Execute_CanMove(this, InValue))
	{
		SetActorLocation(InValue);
	}
}

void AThirdPersonPawn::SetRotation_Implementation(FRotator InValue)
{
	if (Execute_CanTurn(this, InValue))
	{
		SetActorRotation(FRotator(0.f, InValue.Yaw, 0.f));
		SpringArmComponent->SetRelativeRotation(FRotator(InValue.Pitch, 0.f, 0.f), true);
	}
}

void AThirdPersonPawn::SetZoom_Implementation(float InValue)
{
	if (Execute_CanZoom(this, InValue))
	{
		SpringArmComponent->SetTargetArmLength(InValue);
	}
}

FVector AThirdPersonPawn::GetLocation_Implementation()
{
	return GetActorLocation();
}

FRotator AThirdPersonPawn::GetRotation_Implementation()
{
	return FRotator(SpringArmComponent->GetRelativeRotation().Pitch, GetActorRotation().Yaw, 0.f);
}

float AThirdPersonPawn::GetZoom_Implementation()
{
	return SpringArmComponent->TargetArmLength;
}

void AThirdPersonPawn::OnSwitchCameraBegin(UCameraHandle* InCameraHandle)
{
}

void AThirdPersonPawn::OnSwitchCameraFinish(UCameraHandle* InCameraHandle)
{
	if (!IsValid(InCameraHandle) || !IsValid(InCameraHandle->TargetCameraPoint) || !IsValid(InCameraHandle->TargetCameraPoint->GetCameraComponent()))
	{
		DLOG(DLogCamera, Error, TEXT("InCameraPoint/InCameraPoint CameraComponent Is NULL"))
		return;
	}

	FPawnLockState PreviewLockState = Execute_GetPawnLockState(this);
	Execute_SetPawnLockState(this, FPawnLockState());

	if (IsValid(DuplicateCameraComponent))
	{
		DuplicateCameraComponent->MarkAsGarbage();
	}

	const FVector CameraLocation = InCameraHandle->TargetCameraPoint->GetActorLocation();
	const FRotator CameraRotation = InCameraHandle->TargetCameraPoint->GetActorRotation();
	const float CameraSpringArmLength = InCameraHandle->TargetCameraPoint->SpringArmComponent->TargetArmLength;

	DuplicateCameraComponent = DuplicateObject<UCameraComponent>(InCameraHandle->TargetCameraPoint->GetCameraComponent(), this);
	DuplicateCameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Execute_SetLocation(this, CameraLocation);
	Execute_SetRotation(this, CameraRotation);
	SpringArmComponent->SetTargetArmLength(CameraSpringArmLength);

	CameraComponent->SetActive(false);
	DuplicateCameraComponent->SetActive(true);

	Execute_GetPlayerController(this)->PlayerCameraManager->SetViewTarget(this);
	Execute_SetPawnLockState(this, PreviewLockState);
}

UCameraComponent* AThirdPersonPawn::GetActiveCameraComponent_Implementation()
{
	return IsValid(DuplicateCameraComponent) ? DuplicateCameraComponent : (IsValid(CameraComponent) ? CameraComponent : nullptr);
}
