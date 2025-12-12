// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Pawn/ThirdPersonPawn.h"

#include "CameraType.h"
#include "Camera/CameraComponent.h"
#include "CameraSwitch/GenericCameraSwitchMethod.h"
#include "CameraPoint/CameraPointBase.h"
#include "Component/PawnLockStateComponent.h"
#include "Component/PawnSpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/KismetMathLibrary.h"

AThirdPersonPawn::AThirdPersonPawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SpringArmComponent = CreateDefaultSubobject<UPawnSpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AThirdPersonPawn::BeginPlay()
{
	Super::BeginPlay();

	UGenericCameraSwitchMethod::OnSwitchCameraBegin.AddUObject(this, &AThirdPersonPawn::OnSwitchCameraBegin);
	UGenericCameraSwitchMethod::OnSwitchCameraFinish.AddUObject(this, &AThirdPersonPawn::OnSwitchCameraFinish);
}

void AThirdPersonPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGenericCameraSwitchMethod::OnSwitchCameraBegin.RemoveAll(this);
	UGenericCameraSwitchMethod::OnSwitchCameraFinish.RemoveAll(this);

	Super::EndPlay(EndPlayReason);
}

void AThirdPersonPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
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
	const float SpringArmLengthAlpha = FMath::GetMappedRangeValueClamped(FVector2D(100.f, 100000.f), FVector2D(0, 1), SpringArmComponent->TargetArmLength);
	const float SpringArmLengthRate = SpringArmComponent->TargetArmLength * SpringArmLengthAlpha / 100;

	const float Rate = GetMovementBaseSpeed() + SpringArmLengthRate + GetMovementSpeedRate();
	const FVector TargetLocation = GetLocation() + (UKismetMathLibrary::GetRightVector(GetActorRotation()) * InValue.X * Rate) + (UKismetMathLibrary::GetForwardVector(GetActorRotation()) * InValue.Y * Rate);
	Execute_SetLocation(this, TargetLocation);
}

void AThirdPersonPawn::AddRotation_Implementation(FVector2D InValue)
{
	const FRotator TargetRotation = GetRotation() + FRotator(InValue.Y * GetRotationSpeedRate(), InValue.X * GetRotationSpeedRate(), 0.f);
	Execute_SetRotation(this, TargetRotation);
}

void AThirdPersonPawn::AddZoom_Implementation(float InValue)
{
	const float TargetZoom = GetZoom() + InValue * GetZoomSpeedRate();
	if (CanZoom(TargetZoom))
	{
		SpringArmComponent->AddTargetArmLength(InValue * GetZoomSpeedRate());
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

void AThirdPersonPawn::OnSwitchCameraBegin(UGenericCameraSwitchMethod* InCameraHandle)
{
}

void AThirdPersonPawn::OnSwitchCameraFinish(UGenericCameraSwitchMethod* InCameraHandle)
{
	if (!IsValid(InCameraHandle) || !IsValid(InCameraHandle->TargetCameraPoint) || !IsValid(InCameraHandle->TargetCameraPoint->GetCameraComponent()))
	{
		GenericLOG(GenericLogCamera, Error, TEXT("InCameraPoint/InCameraPoint CameraComponent Is InValid"))
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

	if (APlayerController* Player = Cast<APlayerController>(GetController()))
	{
		Player->PlayerCameraManager->SetViewTarget(this);
	}

	Execute_SetPawnLockState(this, PreviewLockState);
}

UCameraComponent* AThirdPersonPawn::GetActiveCameraComponent_Implementation()
{
	return IsValid(DuplicateCameraComponent) ? DuplicateCameraComponent : (IsValid(CameraComponent) ? CameraComponent : nullptr);
}
