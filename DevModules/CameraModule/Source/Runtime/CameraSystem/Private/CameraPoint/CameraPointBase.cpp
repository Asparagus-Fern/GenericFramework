// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPoint/CameraPointBase.h"

#include "CameraManager.h"
#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

#if WITH_EDITOR
#include "LevelEditorSubsystem.h"
#include "LevelEditorViewport.h"
#include "BPFunctions/BPFunctions_EditorScene.h"
#endif

UE_DEFINE_GAMEPLAY_TAG(TAG_Camera, "Camera");

ACameraPointBase::FCameraPointDelegate ACameraPointBase::OnCameraPointRegister;
ACameraPointBase::FCameraPointDelegate ACameraPointBase::OnCameraPointUnRegister;

ACameraPointBase::ACameraPointBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetSphereRadius(30.f);
	SphereComponent->SetEnableGravity(false);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetupAttachment(RootComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringComponent");
	SpringArmComponent->TargetArmLength = 0.f;
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->SetupAttachment(SphereComponent);

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

UCameraComponent* ACameraPointBase::GetCameraComponent_Implementation()
{
	return nullptr;
}

void ACameraPointBase::SetCameraComponent_Implementation(UCameraComponent* InCameraComponent)
{
}

#if WITH_EDITOR

void ACameraPointBase::CopyFromViewportCamera()
{
	Modify();

	SpringArmComponent->TargetArmLength = 0.f;

	const FVector Location = GCurrentLevelEditingViewportClient->GetViewLocation();
	const FRotator Rotation = GCurrentLevelEditingViewportClient->GetViewRotation();

	SetActorLocation(Location);
	SetActorRotation(Rotation);

	RefreshFocus();
}

void ACameraPointBase::RefreshFocus()
{
	FHitResult HitResult;
	UBPFunctions_Gameplay::GetActorForwardHitResult(this, HitResult);
	if (HitResult.bBlockingHit)
	{
		SetActorLocation(HitResult.Location);
		SpringArmComponent->TargetArmLength = HitResult.Distance;
	}

	UBPFunctions_EditorScene::RefreshSelection();
}

void ACameraPointBase::ToggleLock()
{
	GEditor->ToggleSelectedActorMovementLock();
}

void ACameraPointBase::PilotCamera()
{
	ULevelEditorSubsystem* LevelEditorSubsystem = GEditor->GetEditorSubsystem<ULevelEditorSubsystem>();
	LevelEditorSubsystem->PilotLevelActor(this);
}

void ACameraPointBase::EjectPilotCamera()
{
	ULevelEditorSubsystem* LevelEditorSubsystem = GEditor->GetEditorSubsystem<ULevelEditorSubsystem>();
	LevelEditorSubsystem->EjectPilotLevelActor();
}

void ACameraPointBase::DuplicateFromCameraActor(ACameraActor* InCameraActor)
{
	if (IsValid(InCameraActor))
	{
		Modify();

		SpringArmComponent->TargetArmLength = 0.f;
		SetActorLocation(InCameraActor->GetActorLocation());
		SetActorRotation(InCameraActor->GetActorRotation());

		DuplicateFromCameraComponent(InCameraActor->GetCameraComponent());
		RefreshFocus();

		CameraActorLink = nullptr;
	}
}

void ACameraPointBase::DuplicateFromCameraComponent(UCameraComponent* InCameraComponent)
{
	if (IsValid(InCameraComponent))
	{
		UCameraComponent* DuplicateCameraComponent = DuplicateObject<UCameraComponent>(InCameraComponent, this);
		SetCameraComponent(DuplicateCameraComponent);

		UBPFunctions_EditorScene::RefreshSelection();
	}
}

#endif
