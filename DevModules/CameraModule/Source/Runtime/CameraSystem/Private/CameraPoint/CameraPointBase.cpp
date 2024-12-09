// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPoint/CameraPointBase.h"

#include "CameraManager.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

#if WITH_EDITOR
#include "BPFunctions/BPFunctions_EditorScene.h"
#endif

UE_DEFINE_GAMEPLAY_TAG(TAG_Camera, "Camera");

ACameraPointBase::FCameraPointDelegate ACameraPointBase::OnCameraPointRegister;
ACameraPointBase::FCameraPointDelegate ACameraPointBase::OnCameraPointUnRegister;

ACameraPointBase::ACameraPointBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;

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
			DuplicateFromCameraActor(CameraActorLink);
		}
	}
}

#endif

void ACameraPointBase::SetCameraComponent_Implementation(UCameraComponent* InCameraComponent)
{
	SetCameraComponentInternal(InCameraComponent);
}

UCameraComponent* ACameraPointBase::GetCameraComponent_Implementation()
{
	return nullptr;
}

void ACameraPointBase::DuplicateFromCameraActor(ACameraActor* InCameraActor)
{
	if (IsValid(InCameraActor))
	{
		SetActorLocation(InCameraActor->GetActorLocation());
		SetActorRotation(InCameraActor->GetActorRotation());
		DuplicateFromCameraComponent(InCameraActor->GetCameraComponent());

#if WITH_EDITORONLY_DATA
		CameraActorLink = nullptr;
#endif
	}
}

void ACameraPointBase::DuplicateFromCameraComponent(UCameraComponent* InCameraComponent)
{
	if (IsValid(InCameraComponent))
	{
		UCameraComponent* DuplicateCameraComponent = DuplicateObject<UCameraComponent>(InCameraComponent, this);
		SetCameraComponentInternal(DuplicateCameraComponent);
	}
}

void ACameraPointBase::SetCameraComponentInternal(UCameraComponent* InCameraComponent)
{
	if (IsValid(InCameraComponent))
	{
		InCameraComponent->SetRelativeLocation(FVector::ZeroVector);
		InCameraComponent->SetRelativeRotation(FRotator::ZeroRotator);

		InCameraComponent->AttachToComponent(SceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
		InCameraComponent->RegisterComponentWithWorld(GetWorld());

#if WITH_EDITOR
		UBPFunctions_EditorScene::RefreshSelection();
#endif
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
