// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/ThirdPersonPawn.h"

#include "CameraSystemType.h"
#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Camera/CameraComponent.h"
#include "CameraPoint/CameraPointBase.h"
#include "Component/CommonSpringArmComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Handle/CameraHandle.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ManagerGlobal.h"
#include "Pawn/PawnManager.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Pawn_TP, "Pawn.ThirdPerson");

AThirdPersonPawn::AThirdPersonPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	PawnTag = TAG_Pawn_TP;

	Sphere = CreateDefaultSubobject<USphereComponent>("Root");
	Sphere->InitSphereRadius(30.0f);
	Sphere->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = Sphere;

	CommonSpringArmComponent = CreateDefaultSubobject<UCommonSpringArmComponent>("CommonSpringArm");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	// CameraCacheComponent = CreateDefaultSubobject<UCameraComponent>("CameraCache");

	CommonSpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent->SetupAttachment(CommonSpringArmComponent);
	// CameraCacheComponent->SetupAttachment(CommonSpringArmComponent);

	// CameraComponent->SetActive(true);
	// CameraCacheComponent->SetActive(false);
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
		FVector2D Rate = FVector2D(1.f, 1.f);
		float MaxSpeed = 1.f;
		float Acceleration = 1.f;
		float Deceleration = 1.f;

		if (CommonSpringArmComponent->TargetArmLength != 0.f)
		{
			Rate *= CommonSpringArmComponent->TargetArmLength;
			MaxSpeed *= CommonSpringArmComponent->TargetArmLength;
			Acceleration *= CommonSpringArmComponent->TargetArmLength;
			Deceleration *= CommonSpringArmComponent->TargetArmLength;
		}

		FHitResult HitResult;
		if (UBPFunctions_Gameplay::GetComponentDownHitResult(GetActiveCameraComponent(), HitResult))
		{
			Rate += FVector2D(HitResult.Distance, HitResult.Distance) * 1.5;
			MaxSpeed += HitResult.Distance * 3 / 4;
			Acceleration += HitResult.Distance * 1 / 2;
			Deceleration += HitResult.Distance;
		}

		FloatingPawnMovement->MaxSpeed = MaxSpeed;
		FloatingPawnMovement->Acceleration = Acceleration;
		FloatingPawnMovement->Deceleration = Deceleration;

		Super::AddLocation_Implementation(FVector2D(InValue.X * Rate.X, InValue.Y * Rate.Y));
	}
}

void AThirdPersonPawn::AddRotation_Implementation(const FVector2D InValue)
{
	if (CanTurn())
	{
		AddActorWorldRotation(FRotator(0.f, InValue.X, 0.f));

		const FRotator TargetRotation = CommonSpringArmComponent->GetRelativeRotation() + FRotator(-InValue.Y, 0.f, 0.f);
		if (TargetRotation.Pitch > GetManager<UPawnManager>()->MinRotationPitch && TargetRotation.Pitch < GetManager<UPawnManager>()->MaxRotationPitch)
		{
			CommonSpringArmComponent->AddRelativeRotation(FRotator(-InValue.Y, 0.f, 0.f));
		}
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

	/* todo:复制的CameraComponent无效 */
	// CameraComponent = DuplicateObject<UCameraComponent>(InCameraHandle->TargetCameraPoint->GetCameraComponent(), this);

	CameraComponent->SetFieldOfView(InCameraHandle->TargetCameraPoint->GetCameraComponent()->FieldOfView);

	// if (CameraComponent->IsActive())
	// {
	// CameraComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	// CameraComponent->SetActive(false);
	// }

	// CameraComponent->AttachToComponent(CommonSpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// UGameplayStatics::GetPlayerControllerFromID(GetWorld(), 0)->SetViewTarget(this);
	// GetPlayerController()->SetViewTarget(this);

	// CameraComponent->SetActive(false);
	// CameraComponent->SetActiveFlag(true);
	//
	// CameraCacheComponent->SetActive(true);
	// CameraCacheComponent->SetActiveFlag(true);

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
