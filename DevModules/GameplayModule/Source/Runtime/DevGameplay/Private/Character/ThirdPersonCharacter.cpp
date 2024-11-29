// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ThirdPersonCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pawn/Component/PawnSpringArmComponent.h"


AThirdPersonCharacter::AThirdPersonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterName = "ThirdPersonCharacter";

	SpringArmComponent = CreateDefaultSubobject<UPawnSpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	SpringArmComponent->bDoCollisionTest = true;
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bEnableReassessmentSpringArmLength = false;
	SpringArmComponent->SetRelativeLocation(FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - 10.f));

	CameraComponent->FieldOfView = 85.f;
}

void AThirdPersonCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AThirdPersonCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AThirdPersonCharacter::AddLocation_Implementation(FVector2D InValue)
{
	const FVector TargetLocation = Execute_GetLocation(this) + (UKismetMathLibrary::GetRightVector(GetActorRotation()) * InValue.X) + (UKismetMathLibrary::GetForwardVector(GetActorRotation()) * InValue.Y);
	if (Execute_CanMove(this, TargetLocation))
	{
	}

	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.f, GetControlRotation().Yaw, GetControlRotation().Roll)), InValue.X);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.f, GetControlRotation().Yaw, 0.f)), InValue.Y);
}

void AThirdPersonCharacter::AddRotation_Implementation(FVector2D InValue)
{
	const FRotator TargetRotation = Execute_GetRotation(this) + FRotator(InValue.Y, InValue.X, 0.f);
	if (Execute_CanTurn(this, TargetRotation))
	{
		AddControllerYawInput(InValue.X);
		AddControllerPitchInput(InValue.Y);
	}
}

void AThirdPersonCharacter::AddZoom_Implementation(float InValue)
{
	if (Execute_CanZoom(this, SpringArmComponent->TargetArmLength + InValue))
	{
		SpringArmComponent->AddTargetArmLength(InValue);
	}
}

void AThirdPersonCharacter::SetLocation_Implementation(FVector InValue)
{
	if (Execute_CanMove(this, InValue))
	{
		SetActorLocation(InValue);
	}
}

void AThirdPersonCharacter::SetRotation_Implementation(FRotator InValue)
{
	if (Execute_CanTurn(this, InValue))
	{
		SetActorRotation(FRotator(0.f, InValue.Yaw, 0.f));
		SpringArmComponent->SetRelativeRotation(FRotator(InValue.Pitch, 0.f, 0.f), true);
	}
}

void AThirdPersonCharacter::SetZoom_Implementation(float InValue)
{
	if (Execute_CanZoom(this, InValue))
	{
		SpringArmComponent->SetTargetArmLength(InValue);
	}
}

FVector AThirdPersonCharacter::GetLocation_Implementation()
{
	return GetActorLocation();
}

FRotator AThirdPersonCharacter::GetRotation_Implementation()
{
	return GetActorRotation();
	// return FRotator(SpringArmComponent->GetRelativeRotation().Pitch, GetActorRotation().Yaw, 0.f);
}

float AThirdPersonCharacter::GetZoom_Implementation()
{
	return -1;
	// return SpringArmComponent->TargetArmLength;
}
