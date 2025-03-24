// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Pawn/ThirdPersonPawn.h"

#include "Camera/CameraComponent.h"
#include "CameraSwitch/CameraSwitchMethod.h"
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

	UCameraSwitchMethod::OnSwitchCameraBegin.AddUObject(this, &AThirdPersonPawn::OnSwitchCameraBegin);
	UCameraSwitchMethod::OnSwitchCameraFinish.AddUObject(this, &AThirdPersonPawn::OnSwitchCameraFinish);
}

void AThirdPersonPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UCameraSwitchMethod::OnSwitchCameraBegin.RemoveAll(this);
	UCameraSwitchMethod::OnSwitchCameraFinish.RemoveAll(this);

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
	const FVector TargetLocation = GetLocation() + (UKismetMathLibrary::GetRightVector(GetActorRotation()) * InValue.X) + (UKismetMathLibrary::GetForwardVector(GetActorRotation()) * InValue.Y);
	if (CanMove(TargetLocation))
	{
		const float Pitch = UKismetMathLibrary::DegSin(FMath::Abs(GetRotation().Pitch));
		const float Height = Pitch * SpringArmComponent->TargetArmLength;

		const float SpringArmLengthAlpha = FMath::GetMappedRangeValueClamped(LockStateComponent->PawnLockState.SpringArmLimit.SpringArmLengthRange, FVector2D(0, 1), SpringArmComponent->TargetArmLength);
		const float AccelerationRate = FMath::Pow(2, FMath::Sin(SpringArmLengthAlpha));

		FloatingPawnMovement->Acceleration = Height * AccelerationRate * 2;
		FloatingPawnMovement->Deceleration = FloatingPawnMovement->Acceleration / 2;
		FloatingPawnMovement->MaxSpeed = FloatingPawnMovement->Acceleration / 3;

		const FVector2D Movement = InValue * GetMovementSpeedRate() * FMath::Pow(2, Pitch);

		AddMovementInput(UKismetMathLibrary::GetRightVector(GetActorRotation()), Movement.X);
		AddMovementInput(UKismetMathLibrary::GetForwardVector(GetActorRotation()), Movement.Y);
	}
}

void AThirdPersonPawn::AddRotation_Implementation(FVector2D InValue)
{
	const float Pitch = InValue.Y * GetRotationSpeedRate();
	const float Yaw = InValue.X * GetRotationSpeedRate();
	const FRotator TargetRotation = GetRotation() + FRotator(Pitch, Yaw, 0.f);

	// DLOG(DLogDefault, Warning, TEXT("TargetRotation : %s"), *TargetRotation.ToString())

	if (CanTurn(TargetRotation))
	{
		AddActorWorldRotation(FRotator(0.f, Yaw, 0.f));
		SpringArmComponent->AddRelativeRotation(FRotator(Pitch, 0.f, 0.f));
	}
}

void AThirdPersonPawn::AddZoom_Implementation(float InValue)
{
	if (CanZoom(SpringArmComponent->TargetArmLength + InValue))
	{
		SpringArmComponent->AddTargetArmLength(InValue);
	}
}

void AThirdPersonPawn::SetLocation_Implementation(FVector InValue)
{
	if (CanMove(InValue))
	{
		SetActorLocation(InValue);
	}
}

void AThirdPersonPawn::SetRotation_Implementation(FRotator InValue)
{
	if (CanTurn(InValue))
	{
		SetActorRotation(FRotator(0.f, InValue.Yaw, 0.f));
		SpringArmComponent->SetRelativeRotation(FRotator(InValue.Pitch, 0.f, 0.f), true);
	}
}

void AThirdPersonPawn::SetZoom_Implementation(float InValue)
{
	if (CanZoom(InValue))
	{
		SpringArmComponent->SetTargetArmLength(InValue);
	}
}

FVector AThirdPersonPawn::GetLocation()
{
	return GetActorLocation();
}

FRotator AThirdPersonPawn::GetRotation()
{
	return FRotator(SpringArmComponent->GetRelativeRotation().Pitch, GetActorRotation().Yaw, 0.f);
}

float AThirdPersonPawn::GetZoom()
{
	return SpringArmComponent->TargetArmLength;
}

void AThirdPersonPawn::OnSwitchCameraBegin(UCameraSwitchMethod* InCameraHandle)
{
}

void AThirdPersonPawn::OnSwitchCameraFinish(UCameraSwitchMethod* InCameraHandle)
{
	if (!IsValid(InCameraHandle) || !IsValid(InCameraHandle->TargetCameraPoint) || !IsValid(InCameraHandle->TargetCameraPoint->GetCameraComponent()))
	{
		DLOG(DLogCamera, Error, TEXT("InCameraPoint/InCameraPoint CameraComponent Is NULL"))
		return;
	}

	FPawnLockState PreviewLockState = GetPawnLockState();
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

	GetPlayerController()->PlayerCameraManager->SetViewTarget(this);
	Execute_SetPawnLockState(this, PreviewLockState);
}

UCameraComponent* AThirdPersonPawn::GetActiveCameraComponent_Implementation()
{
	return IsValid(DuplicateCameraComponent) ? DuplicateCameraComponent : (IsValid(CameraComponent) ? CameraComponent : nullptr);
}
