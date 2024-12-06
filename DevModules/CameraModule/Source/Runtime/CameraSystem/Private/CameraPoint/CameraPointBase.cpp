// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPoint/CameraPointBase.h"

#include "CameraManager.h"
#include "Camera/CameraActor.h"
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

#if WITH_EDITOR

void ACameraPointBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property)
	{
		const FName PropertyName = PropertyChangedEvent.Property->GetFName();

		if (PropertyName == GET_MEMBER_NAME_CHECKED(ACameraPointBase, CameraActorLink))
		{
			SetCameraActorLink(CameraActorLink);
		}
	}
}

#endif

void ACameraPointBase::SetCameraComponent_Implementation(UCameraComponent* InCameraComponent)
{
}

UCameraComponent* ACameraPointBase::GetCameraComponent_Implementation()
{
	return nullptr;
}

void ACameraPointBase::SetCameraActorLink(ACameraActor* InCameraActor)
{
	if (IsValid(InCameraActor))
	{
		SetActorLocation(InCameraActor->GetActorLocation());
		SetCameraComponentLink(InCameraActor->GetCameraComponent());

#if WITH_EDITORONLY_DATA
		CameraActorLink = nullptr;
#endif
	}
}

void ACameraPointBase::SetCameraComponentLink(UCameraComponent* InCameraComponent)
{
	if (IsValid(InCameraComponent))
	{
		UCameraComponent* DuplicateCameraComponent = DuplicateObject<UCameraComponent>(InCameraComponent, this);
		SetCameraComponentInternal(DuplicateCameraComponent);
	}
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
