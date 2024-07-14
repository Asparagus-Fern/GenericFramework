// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/ThirdPersonPawn.h"

#include "CameraSystemType.h"
#include "Camera/CameraComponent.h"
#include "CameraPoint/CameraPointBase.h"
#include "Component/CommonSpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "Handle/CameraHandle.h"

AThirdPersonPawn::AThirdPersonPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	Sphere = CreateDefaultSubobject<USphereComponent>("Root");
	Sphere->InitSphereRadius(30.0f);
	Sphere->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = Sphere;

	CommonSpringArmComponent = CreateDefaultSubobject<UCommonSpringArmComponent>("CommonSpringArm");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraCacheComponent = CreateDefaultSubobject<UCameraComponent>("CameraCache");

	CommonSpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(CommonSpringArmComponent);
	CameraCacheComponent->SetupAttachment(CommonSpringArmComponent);

	CameraComponent->SetActive(true);
	CameraCacheComponent->SetActive(false);
}

void AThirdPersonPawn::BeginPlay()
{
	Super::BeginPlay();

	FCameraSystemDelegates::OnSwitchCameraFinish.AddUObject(this, &AThirdPersonPawn::OnSwitchCameraFinish);
}

void AThirdPersonPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AThirdPersonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UCameraComponent* AThirdPersonPawn::GetActiveCameraComponent() const
{
	return IsValid(CameraCacheComponent) ? (CameraCacheComponent->IsActive() ? CameraCacheComponent : CameraComponent) : CameraComponent;
}

void AThirdPersonPawn::OnRefresh_Implementation()
{
	Super::OnRefresh_Implementation();
	RefreshSpringArmComponent();
}

void AThirdPersonPawn::AddLocation_Implementation(FVector2D InValue)
{
	if (CanMove())
	{
		Super::AddLocation_Implementation(FVector2D(InValue.X * CommonSpringArmComponent->TargetArmLength, InValue.Y * CommonSpringArmComponent->TargetArmLength));
	}
}

void AThirdPersonPawn::AddRotation_Implementation(const FVector2D InValue)
{
	if (CanMove())
	{
		AddActorWorldRotation(FRotator(0.f, InValue.X, 0.f));
		CommonSpringArmComponent->AddRelativeRotation(FRotator(-InValue.Y, 0.f, 0.f));
	}
}

void AThirdPersonPawn::SetRotation_Implementation(const FRotator InValue)
{
	if (CanTurn())
	{
		SetActorRotation(FRotator(0.f, InValue.Yaw, 0.f));
		CommonSpringArmComponent->SetRelativeRotation(FRotator(InValue.Pitch, 0.f, 0.f), true);
	}
}

FRotator AThirdPersonPawn::GetRotation_Implementation()
{
	return FRotator(CommonSpringArmComponent->GetRelativeRotation().Pitch, GetActorRotation().Yaw, 0.f);
}

FRotator AThirdPersonPawn::GetCameraRotation_Implementation()
{
	return Execute_GetRotation(this);
}

void AThirdPersonPawn::OnSwitchCameraFinish(UCameraHandle* InCameraHandle)
{
	if (!IsValid(InCameraHandle) || !IsValid(InCameraHandle->TargetCameraPoint) || !IsValid(InCameraHandle->TargetCameraPoint->GetCameraComponent()))
	{
		DEBUG(Debug_Camera, Error, TEXT("InCameraPoint/InCameraPoint CameraComponent Is NULL"))
		return;
	}

	CameraCacheComponent = DuplicateObject<UCameraComponent>(InCameraHandle->TargetCameraPoint->GetCameraComponent(), this);
	CameraCacheComponent->AttachToComponent(CommonSpringArmComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	CameraComponent->SetActive(false);
	CameraCacheComponent->SetActive(true);

	CommonSpringArmComponent->SetTargetArmLength(0.f);
	Execute_SetLocation(this, InCameraHandle->TargetCameraPoint->GetActorLocation());
	Execute_SetRotation(this, InCameraHandle->TargetCameraPoint->GetActorRotation());

	FHitResult HitResult;
	if (GetHitResult(HitResult))
	{
		Execute_SetLocation(this, HitResult.Location);
		CommonSpringArmComponent->SetTargetArmLength(HitResult.Distance);
	}
	else
	{
		CommonSpringArmComponent->SetTargetArmLength(0.f);
	}

	UpdateLockState(InCameraHandle->bLock, InCameraHandle->bLockLocation, InCameraHandle->bLockRotation);
}

void AThirdPersonPawn::RefreshSpringArmComponent()
{
	FHitResult HitResult;
	if (GetHitResult(HitResult))
	{
		Execute_SetLocation(this, HitResult.Location);
		CommonSpringArmComponent->SetTargetArmLength(HitResult.Distance);
	}
}

bool AThirdPersonPawn::GetHitResult(FHitResult& HitResult)
{
	const FVector Start = Execute_GetLocation(this);
	const FVector End = GetActiveCameraComponent()->GetForwardVector() * UE_BIG_NUMBER + Start;
	return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);
}
