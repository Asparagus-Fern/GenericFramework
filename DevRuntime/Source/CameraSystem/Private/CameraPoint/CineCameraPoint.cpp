// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraPoint/CineCameraPoint.h"

#include "CineCameraComponent.h"

ACineCameraPoint::ACineCameraPoint()
{
	CineCameraComponent = CreateDefaultSubobject<UCineCameraComponent>("CineCamera");
	RootComponent = CineCameraComponent;
}

UCameraComponent* ACineCameraPoint::GetCameraComponent_Implementation()
{
	return CineCameraComponent;
}

void ACineCameraPoint::SetCameraComponent_Implementation(UCameraComponent* InCameraComponent)
{
	if (UCineCameraComponent* CastComponent = Cast<UCineCameraComponent>(InCameraComponent))
	{
		CineCameraComponent = CastComponent;
	}
	else
	{
		Super::SetCameraComponent_Implementation(InCameraComponent);
	}
}
