// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/ThirdPersonPawn.h"

#include "CameraManager.h"
#include "CameraPoint.h"
#include "CameraSystemType.h"
#include "Camera/CameraComponent.h"
#include "Component/CommonSpringArmComponent.h"
#include "Components/SphereComponent.h"

AThirdPersonPawn::AThirdPersonPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	Sphere = CreateDefaultSubobject<USphereComponent>("Root");
	Sphere->InitSphereRadius(30.0f);
	Sphere->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = Sphere;

	CommonSpringArmComponent = CreateDefaultSubobject<UCommonSpringArmComponent>("CommonSpringArm");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");

	CommonSpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(CommonSpringArmComponent);
}

void AThirdPersonPawn::BeginPlay()
{
	Super::BeginPlay();

	FCameraSystemDelegates::PreSwitchCamera.AddUObject(this, &AThirdPersonPawn::PreSwitchCamera);
	FCameraSystemDelegates::PostSwitchCamera.AddUObject(this, &AThirdPersonPawn::PostSwitchCamera);
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
	return CameraCacheComponent->IsActive() ? CameraCacheComponent : (CameraComponent->IsActive() ? CameraComponent : nullptr);
}

void AThirdPersonPawn::AddLocation_Implementation(FVector2D InValue)
{
	const float CameraHeight = GetPlayerController()->PlayerCameraManager->GetCameraLocation().Z - GetActorLocation().Z;
	const float TargetArmLength = CommonSpringArmComponent->TargetArmLength;
	float Degree = (180.0) / UE_DOUBLE_PI * FMath::Asin(CameraHeight / TargetArmLength);
	Degree = FMath::GetMappedRangeValueClamped(FVector2D(-90.f, 90.f), FVector2D(0.f, 90.f), Degree);

	Super::AddLocation_Implementation(FVector2D(InValue.X * CommonSpringArmComponent->TargetArmLength, InValue.Y * CommonSpringArmComponent->TargetArmLength));
}

void AThirdPersonPawn::AddRotation_Implementation(const FVector2D InValue)
{
	AddActorWorldRotation(FRotator(0.f, InValue.X, 0.f));
	CommonSpringArmComponent->AddRelativeRotation(FRotator(-InValue.Y, 0.f, 0.f));
}

FRotator AThirdPersonPawn::GetRotation_Implementation()
{
	return FRotator(CommonSpringArmComponent->GetRelativeRotation().Pitch, GetActorRotation().Yaw, 0.f);
}

void AThirdPersonPawn::SetRotation_Implementation(const FRotator InValue)
{
	SetActorRotation(FRotator(0.f, InValue.Yaw, 0.f));
	CommonSpringArmComponent->SetRelativeRotation(FRotator(InValue.Pitch, 0.f, 0.f), true);
}

void AThirdPersonPawn::RefreshTransform_Implementation()
{
	Super::RefreshTransform_Implementation();
}

void AThirdPersonPawn::PreSwitchCamera(ACameraPoint* InCameraPoint)
{
}

void AThirdPersonPawn::PostSwitchCamera(ACameraPoint* InCameraPoint)
{
	CameraCacheComponent = DuplicateObject<UCameraComponent>(InCameraPoint->CameraComponent, this);
	CameraCacheComponent->AttachToComponent(CommonSpringArmComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

	CameraComponent->SetActive(false);
	CameraCacheComponent->SetActive(true);

	CommonSpringArmComponent->SetTargetArmLength(0.f);
	Execute_SetLocation(this, InCameraPoint->GetActorLocation());
	Execute_SetRotation(this, InCameraPoint->GetActorRotation());

	FHitResult HitResult;
	if (GetHitResult(HitResult))
	{
		Execute_SetLocation(this, HitResult.Location);
		CommonSpringArmComponent->SetTargetArmLength(HitResult.Distance);
	}
	else
	{
		Execute_SetLocation(this, GetActiveCameraComponent()->GetForwardVector() * 1000 + Execute_GetLocation(this));
		CommonSpringArmComponent->SetTargetArmLength(1000.f);
	}
}

bool AThirdPersonPawn::GetHitResult(FHitResult& HitResult)
{
	const FVector Start = Execute_GetLocation(this);
	const FVector End = GetActiveCameraComponent()->GetForwardVector() * UE_BIG_NUMBER + Start;
	return GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Camera);
}
