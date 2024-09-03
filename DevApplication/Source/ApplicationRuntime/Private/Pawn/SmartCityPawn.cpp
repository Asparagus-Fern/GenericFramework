// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/SmartCityPawn.h"

#include "CameraHandle.h"
#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Camera/CameraComponent.h"
#include "CameraPoint/CameraPointBase.h"
#include "Component/CommonSpringArmComponent.h"
#include "Kismet/GameplayStatics.h"


ASmartCityPawn::ASmartCityPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASmartCityPawn::BeginPlay()
{
	Super::BeginPlay();
	UCameraHandle::OnSwitchCameraBegin.AddUObject(this, &ASmartCityPawn::OnSwitchCameraBegin);
	UCameraHandle::OnSwitchCameraFinish.AddUObject(this, &ASmartCityPawn::OnSwitchCameraFinish);
}

void ASmartCityPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UCameraHandle::OnSwitchCameraBegin.RemoveAll(this);
	UCameraHandle::OnSwitchCameraFinish.RemoveAll(this);
	Super::EndPlay(EndPlayReason);
}

void ASmartCityPawn::CalcCamera(float DeltaTime, FMinimalViewInfo& OutResult)
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

UCameraComponent* ASmartCityPawn::GetActiveCameraComponent_Implementation()
{
	return IsValid(DuplicateCameraComponent) ? DuplicateCameraComponent : Super::GetActiveCameraComponent_Implementation();
}

void ASmartCityPawn::OnSwitchCameraBegin(UCameraHandle* InCameraHandle)
{
}

void ASmartCityPawn::OnSwitchCameraFinish(UCameraHandle* InCameraHandle)
{
	if (!IsValid(InCameraHandle) || !IsValid(InCameraHandle->TargetCameraPoint) || !IsValid(InCameraHandle->TargetCameraPoint->GetCameraComponent()))
	{
		LOG(Debug_Camera, Error, TEXT("InCameraPoint/InCameraPoint CameraComponent Is NULL"))
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

	DuplicateCameraComponent->AttachToComponent(CommonSpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	CommonSpringArmComponent->SetTargetArmLength(0.01f);
	Execute_SetLocation(this, CameraLocation);
	Execute_SetRotation(this, CameraRotation);

	FHitResult HitResult;
	const FVector Start = Execute_GetLocation(this);
	const FVector End = GetActiveCameraComponent()->GetForwardVector() * UE_BIG_NUMBER + Start;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
	{
		Execute_SetLocation(this, HitResult.Location);
		CommonSpringArmComponent->SetTargetArmLength(HitResult.Distance);
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
