// Copyright ChenTaiye 2025. All Rights Reserved.

#include "CameraPoint/GenericCameraPoint.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AGenericCameraPoint::AGenericCameraPoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

UCameraComponent* AGenericCameraPoint::GetCameraComponent_Implementation()
{
	return CameraComponent;
}

void AGenericCameraPoint::SetCameraComponent_Implementation(UCameraComponent* InCameraComponent)
{
	Super::SetCameraComponent_Implementation(InCameraComponent);

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
}