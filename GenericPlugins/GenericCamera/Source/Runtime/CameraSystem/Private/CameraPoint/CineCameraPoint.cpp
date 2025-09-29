// Copyright ChenTaiye 2025. All Rights Reserved.

#include "CameraPoint/CineCameraPoint.h"

#include "CineCameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACineCameraPoint::ACineCameraPoint(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CineCameraComponent = CreateDefaultSubobject<UCineCameraComponent>("CineCamera");
	CineCameraComponent->SetupAttachment(SpringArmComponent);
}

UCameraComponent* ACineCameraPoint::GetCameraComponent_Implementation()
{
	return CineCameraComponent;
}

void ACineCameraPoint::SetCameraComponent_Implementation(UCameraComponent* InCameraComponent)
{
	Super::SetCameraComponent_Implementation(InCameraComponent);

	if (IsValid(InCameraComponent))
	{
		if (UCineCameraComponent* CastComponent = Cast<UCineCameraComponent>(InCameraComponent))
		{
			CineCameraComponent->SetFilmback(CastComponent->Filmback);
			CineCameraComponent->SetLensSettings(CastComponent->LensSettings);
			CineCameraComponent->SetFocusSettings(CastComponent->FocusSettings);
			CineCameraComponent->SetCropSettings(CastComponent->CropSettings);
			CineCameraComponent->SetCurrentFocalLength(CastComponent->CurrentFocalLength);
			CineCameraComponent->SetCurrentAperture(CastComponent->CurrentAperture);
			CineCameraComponent->SetFieldOfView(CastComponent->FieldOfView);
			CineCameraComponent->SetCustomNearClippingPlane(CastComponent->CustomNearClippingPlane);
		}
	}
}
