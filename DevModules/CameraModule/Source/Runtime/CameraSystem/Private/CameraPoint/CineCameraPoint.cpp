// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraPoint/CineCameraPoint.h"

#include "CineCameraComponent.h"
#include "Camera/CameraActor.h"

ACineCameraPoint::ACineCameraPoint()
{
	CineCameraComponent = CreateDefaultSubobject<UCineCameraComponent>("CineCamera");
	CineCameraComponent->SetupAttachment(SceneComponent);
}

UCameraComponent* ACineCameraPoint::GetCameraComponent_Implementation()
{
	return CineCameraComponent;
}

void ACineCameraPoint::SetCameraComponentInternal(UCameraComponent* InCameraComponent)
{
	if (IsValid(InCameraComponent))
	{
		if (UCineCameraComponent* CastComponent = Cast<UCineCameraComponent>(InCameraComponent))
		{
			// CineCameraComponent->DestroyComponent();
			// CineCameraComponent = Cast<UCineCameraComponent>(GetRootComponent());
		}
	}

	Super::SetCameraComponentInternal(InCameraComponent);
}
