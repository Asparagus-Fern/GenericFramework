// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPoint/CameraPoint.h"

#include "Camera/CameraComponent.h"

ACameraPoint::ACameraPoint()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	RootComponent = CameraComponent;
}

UCameraComponent* ACameraPoint::GetCameraComponent_Implementation()
{
	return CameraComponent;
}

void ACameraPoint::SetCameraComponent_Implementation(UCameraComponent* InCameraComponent)
{
	CameraComponent = InCameraComponent;
}
