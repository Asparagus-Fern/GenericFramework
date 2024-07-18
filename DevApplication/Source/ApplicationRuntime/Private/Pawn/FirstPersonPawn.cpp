// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/FirstPersonPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_Pawn_FP, "Pawn.FirstPerson");

AFirstPersonPawn::AFirstPersonPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	PawnTag = TAG_Pawn_FP;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("Root");
	Capsule->SetCapsuleHalfHeight(85.f);
	Capsule->SetCapsuleRadius(30.f);
	Capsule->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	RootComponent = Capsule;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(Capsule);
	CameraComponent->SetRelativeLocation(FVector(0.f, 0.f, Capsule->GetScaledCapsuleHalfHeight()));
}

void AFirstPersonPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AFirstPersonPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFirstPersonPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AFirstPersonPawn::AddRotation_Implementation(FVector2D InValue)
{
	Super::AddRotation_Implementation(InValue);
}
