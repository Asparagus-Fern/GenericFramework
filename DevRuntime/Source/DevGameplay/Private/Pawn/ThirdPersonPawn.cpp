// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/ThirdPersonPawn.h"

#include "Camera/CameraComponent.h"
#include "CameraHandle/CameraHandle.h"
#include "CameraPoint/CameraPointBase.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pawn/DSpringArmComponent.h"


AThirdPersonPawn::AThirdPersonPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PawnName = "ThirdPersonPawn";

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");

	SpringArmComponent = CreateDefaultSubobject<UDSpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AThirdPersonPawn::BeginPlay()
{
	Super::BeginPlay();
	SpringArmComponent->SpringArmLimit = PawnLockingState.SpringArmLimit;

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
	if (PawnLockingState.CanMove(TargetLocation))
	{
		const float Rate = FMath::Abs(FMath::GetMappedRangeValueClamped(FVector2D(0.f, 1.f), FVector2D(0.1f, 0.9f), FMath::Sin(UE_DOUBLE_PI / (180.0) * Execute_GetRotation(this).Pitch))) * SpringArmComponent->TargetArmLength * UE_TWO_PI;
		const float MovementRate = 1.5f;

		FloatingPawnMovement->MaxSpeed = Rate * MovementRate * 1.2f;
		FloatingPawnMovement->Acceleration = Rate * MovementRate * 2.f;
		FloatingPawnMovement->Deceleration = Rate * MovementRate * 2.5f;

		const FVector2D Movement = InValue * MovementSpeed;
		AddMovementInput(UKismetMathLibrary::GetRightVector(GetActorRotation()), Movement.X);
		AddMovementInput(UKismetMathLibrary::GetForwardVector(GetActorRotation()), Movement.Y);
	}
}

void AThirdPersonPawn::AddRotation_Implementation(FVector2D InValue)
{
	const FRotator TargetRotation = Execute_GetRotation(this) + FRotator(InValue.Y, InValue.X, 0.f);
	if (PawnLockingState.CanTurn(TargetRotation))
	{
		AddActorWorldRotation(FRotator(0.f, InValue.X * RotationSpeed, 0.f));
		SpringArmComponent->AddRelativeRotation(FRotator(InValue.Y * RotationSpeed, 0.f, 0.f));
	}
}

void AThirdPersonPawn::AddZoom_Implementation(float InValue)
{
	if (PawnLockingState.CanZoom(SpringArmComponent->TargetArmLength + InValue))
	{
		SpringArmComponent->AddTargetArmLength(InValue);
	}
}

void AThirdPersonPawn::SetLocation_Implementation(FVector InValue)
{
	if (PawnLockingState.CanMove(InValue))
	{
		SetActorLocation(InValue);
	}
}

void AThirdPersonPawn::SetRotation_Implementation(FRotator InValue)
{
	if (PawnLockingState.CanTurn(InValue))
	{
		SetActorRotation(FRotator(0.f, InValue.Yaw, 0.f));
		SpringArmComponent->SetRelativeRotation(FRotator(InValue.Pitch, 0.f, 0.f), true);
	}
}

void AThirdPersonPawn::SetZoom_Implementation(float InValue)
{
	if (PawnLockingState.CanZoom(InValue))
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

UCameraComponent* AThirdPersonPawn::GetActiveCameraComponent_Implementation()
{
	return IsValid(DuplicateCameraComponent) ? DuplicateCameraComponent : (IsValid(CameraComponent) ? CameraComponent : Super::GetActiveCameraComponent_Implementation());
}

void AThirdPersonPawn::SetPawnLockingState_Implementation(FPawnLockingState InPawnLockingState)
{
	Super::SetPawnLockingState_Implementation(InPawnLockingState);
	SpringArmComponent->SpringArmLimit = PawnLockingState.SpringArmLimit;
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

	if (IsValid(DuplicateCameraComponent))
	{
		DuplicateCameraComponent->MarkAsGarbage();
	}

	const FVector CameraLocation = InCameraHandle->TargetCameraPoint->GetActorLocation();
	const FRotator CameraRotation = InCameraHandle->TargetCameraPoint->GetActorRotation();

	DuplicateCameraComponent = DuplicateObject<UCameraComponent>(InCameraHandle->TargetCameraPoint->GetCameraComponent(), this);
	DuplicateCameraComponent->SetRelativeLocation(FVector::ZeroVector);
	DuplicateCameraComponent->SetRelativeRotation(FRotator::ZeroRotator);

	DuplicateCameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	SpringArmComponent->SetTargetArmLength(0.01f);
	Execute_SetLocation(this, CameraLocation);
	Execute_SetRotation(this, CameraRotation);

	FHitResult HitResult;
	const FVector Start = Execute_GetLocation(this);
	const FVector End = GetActiveCameraComponent()->GetForwardVector() * UE_BIG_NUMBER + Start;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
	{
		Execute_SetLocation(this, HitResult.Location);
		SpringArmComponent->SetTargetArmLength(HitResult.Distance);
	}

	CameraComponent->SetActive(false);
	DuplicateCameraComponent->SetActive(true);

	FViewTargetTransitionParams ViewTargetTransitionParams;
	ViewTargetTransitionParams.BlendTime = 0.5f;

	FMinimalViewInfo MinimalViewInfo;
	DuplicateCameraComponent->GetCameraView(0.f, MinimalViewInfo);

	Execute_GetPlayerController(this)->PlayerCameraManager->SetViewTarget(this);
	// Execute_GetPlayerController(this)->PlayerCameraManager->SetFOV(DuplicateCameraComponent->FieldOfView);
	// Execute_GetPlayerController(this)->PlayerCameraManager->UpdateCamera(0.f);
}
