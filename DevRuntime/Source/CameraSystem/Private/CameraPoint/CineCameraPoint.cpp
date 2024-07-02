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
