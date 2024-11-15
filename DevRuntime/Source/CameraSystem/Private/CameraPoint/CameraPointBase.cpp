// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPoint/CameraPointBase.h"

#include "CameraManager.h"
#include "Camera/CameraComponent.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Camera, "Camera");

ACameraPointBase::FCameraPointDelegate ACameraPointBase::OnCameraPointRegister;
ACameraPointBase::FCameraPointDelegate ACameraPointBase::OnCameraPointUnRegister;

ACameraPointBase::ACameraPointBase()
{
	PrimaryActorTick.bCanEverTick = false;

#if WITH_EDITORONLY_DATA
	bIsSpatiallyLoaded = true;
#endif
}

void ACameraPointBase::BeginPlay()
{
	Super::BeginPlay();
	OnCameraPointRegister.Broadcast(this);
}

void ACameraPointBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnCameraPointUnRegister.Broadcast(this);
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

ACameraPointBase::FCameraPointDelegate ACameraPointBase::OnCopyViewportCamera;
ACameraPointBase::FOnCameraPointPilotStateChanged ACameraPointBase::OnCameraPointPilotStateChanged;

void ACameraPointBase::CopyFromViewportCamera_Implementation()
{
	OnCopyViewportCamera.Broadcast(this);
}

void ACameraPointBase::PilotCamera_Implementation()
{
	OnCameraPointPilotStateChanged.Broadcast(this, true);
}

void ACameraPointBase::StopPilotCamera_Implementation()
{
	OnCameraPointPilotStateChanged.Broadcast(this, false);
}

#endif
