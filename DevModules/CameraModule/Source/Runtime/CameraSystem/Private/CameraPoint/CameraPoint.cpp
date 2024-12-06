// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPoint/CameraPoint.h"

#include "Camera/CameraActor.h"
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
	SetCameraComponentInternal(InCameraComponent);
}

void ACameraPoint::SetCameraComponentInternal(UCameraComponent* InCameraComponent)
{
	if (IsValid(InCameraComponent))
	{
		AddComponent()

		
		SetRootComponent(InCameraComponent);
		InCameraComponent->RegisterComponent();
		CameraComponent = Cast<UCameraComponent>(GetRootComponent());
	}
}
