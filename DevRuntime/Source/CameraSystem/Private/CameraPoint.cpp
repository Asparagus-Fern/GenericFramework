// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPoint.h"

#include "CameraManager.h"
#include "CameraSystemType.h"
#include "Camera/CameraComponent.h"
#include "Handle/CameraHandle_Default.h"

ACameraPoint::ACameraPoint()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	RootComponent = CameraComponent;

	CameraHandle = CreateDefaultSubobject<UCameraHandle_Default>("CameraHandle");
	bIsSpatiallyLoaded = true;
}

void ACameraPoint::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void ACameraPoint::BeginPlay()
{
	Super::BeginPlay();
	UCameraManager::Get()->AddCameraPoint(CameraTag, this);
}

void ACameraPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UCameraManager::Get()->RemoveCameraPoint(CameraTag);
	Super::EndPlay(EndPlayReason);
}

#if WITH_EDITOR

void ACameraPoint::CopyFromViewportCamera_Implementation()
{
	FCameraSystemDelegates::OnCopyViewportCamera.Broadcast(this);
}

void ACameraPoint::PilotCamera_Implementation()
{
	FCameraSystemDelegates::OnCameraPointPilotStateChanged.Broadcast(this, true);
}

void ACameraPoint::StopPilotCamera_Implementation()
{
	FCameraSystemDelegates::OnCameraPointPilotStateChanged.Broadcast(this, false);
}

#endif
