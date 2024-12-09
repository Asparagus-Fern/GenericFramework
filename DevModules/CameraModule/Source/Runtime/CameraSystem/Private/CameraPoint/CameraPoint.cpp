// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPoint/CameraPoint.h"

#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"

ACameraPoint::ACameraPoint()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SceneComponent);
}

UCameraComponent* ACameraPoint::GetCameraComponent_Implementation()
{
	return CameraComponent;
}

void ACameraPoint::SetCameraComponentInternal(UCameraComponent* InCameraComponent)
{
	if (IsValid(InCameraComponent))
	{
		/* todo: 拷贝的CameraComponent被未知移除掉了 */
		// CameraComponent->DestroyComponent();
		// CameraComponent = InCameraComponent;

		CameraComponent->SetProjectionMode(InCameraComponent->ProjectionMode);
		CameraComponent->SetFieldOfView(InCameraComponent->FieldOfView);
		CameraComponent->SetAspectRatio(InCameraComponent->AspectRatio);

		CameraComponent->SetConstraintAspectRatio(InCameraComponent->bConstrainAspectRatio);
		CameraComponent->bUsePawnControlRotation = InCameraComponent->bUsePawnControlRotation;
		CameraComponent->SetPostProcessBlendWeight(InCameraComponent->PostProcessBlendWeight);
		CameraComponent->SetAspectRatioAxisConstraint(InCameraComponent->AspectRatioAxisConstraint);
		CameraComponent->bOverrideAspectRatioAxisConstraint = InCameraComponent->bOverrideAspectRatioAxisConstraint;
		CameraComponent->bLockToHmd = InCameraComponent->bLockToHmd;
		CameraComponent->SetUseFieldOfViewForLOD(InCameraComponent->bUseFieldOfViewForLOD);

		CameraComponent->SetOrthoWidth(InCameraComponent->OrthoWidth);
		CameraComponent->PostProcessSettings = InCameraComponent->PostProcessSettings;
	}

	// Super::SetCameraComponentInternal(InCameraComponent);
}
