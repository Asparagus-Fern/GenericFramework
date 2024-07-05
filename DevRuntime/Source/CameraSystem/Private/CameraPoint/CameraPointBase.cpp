// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPoint/CameraPointBase.h"

#include "CameraManager.h"
#include "CameraSystemType.h"
#include "Handle/CameraHandle_Default.h"
#include "Manager/ManagerGlobal.h"


ACameraPointBase::ACameraPointBase()
{
	CameraHandle = CreateDefaultSubobject<UCameraHandle_Default>("CameraHandle");
	bIsSpatiallyLoaded = true;
	PrimaryActorTick.bCanEverTick = true;
}

void ACameraPointBase::BeginPlay()
{
	Super::BeginPlay();
	GetManager<UCameraManager>()->AddCameraPoint(CameraTag, this);
}

void ACameraPointBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetManager<UCameraManager>()->RemoveCameraPoint(CameraTag);
	Super::EndPlay(EndPlayReason);
}

void ACameraPointBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACameraPointBase::SetCameraComponent_Implementation(UCameraComponent* InCameraComponent)
{
}

UCameraComponent* ACameraPointBase::GetCameraComponent_Implementation()
{
	return nullptr;
}

#if WITH_EDITOR

void ACameraPointBase::CopyFromViewportCamera_Implementation()
{
	FCameraSystemDelegates::OnCopyViewportCamera.Broadcast(this);
}

void ACameraPointBase::PilotCamera_Implementation()
{
	FCameraSystemDelegates::OnCameraPointPilotStateChanged.Broadcast(this, true);
}

void ACameraPointBase::StopPilotCamera_Implementation()
{
	FCameraSystemDelegates::OnCameraPointPilotStateChanged.Broadcast(this, false);
}

#endif
