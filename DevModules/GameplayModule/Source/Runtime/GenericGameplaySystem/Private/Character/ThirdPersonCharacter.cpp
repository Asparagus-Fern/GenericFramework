// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Character/ThirdPersonCharacter.h"

#include "Camera/CameraComponent.h"
#include "Component/PawnSpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"

AThirdPersonCharacter::AThirdPersonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<UPawnSpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	SpringArmComponent->bDoCollisionTest = true;
	SpringArmComponent->TargetArmLength = 300.f;
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bEnableReassessmentFocus = false;
	SpringArmComponent->SetRelativeLocation(FVector(0.f, 0.f, GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - 10.f));

	CameraComponent->FieldOfView = 85.f;

	if (USkeletalMeshComponent* MeshComponent = GetMesh())
	{
		if (USkeletalMesh* FoundSkeletalMesh = LoadObject<USkeletalMesh>(nullptr,TEXT("/Script/Engine.SkeletalMesh'/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple'")))
		{
			MeshComponent->SetSkeletalMesh(FoundSkeletalMesh);
		}

		if (TSubclassOf<UAnimInstance> FoundAnimClass = LoadClass<UAnimInstance>(nullptr,TEXT("/Script/Engine.AnimBlueprint'/Mannequins/Animations/ABP_Quinn.ABP_Quinn_C'")))
		{
			MeshComponent->SetAnimInstanceClass(FoundAnimClass);
		}

		MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -88.f));
		MeshComponent->SetRelativeRotation(FRotator(0.f, 270.f, 0.f));
	}
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
	const FVector TargetLocation = GetLocation() + (UKismetMathLibrary::GetRightVector(GetActorRotation()) * InValue.X) + (UKismetMathLibrary::GetForwardVector(GetActorRotation()) * InValue.Y);
	if (CanMove(TargetLocation))
	{
	}

	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.f, GetControlRotation().Yaw, GetControlRotation().Roll)), InValue.X);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.f, GetControlRotation().Yaw, 0.f)), InValue.Y);
}

void AThirdPersonCharacter::AddRotation_Implementation(FVector2D InValue)
{
	const FRotator TargetRotation = GetRotation() + FRotator(InValue.Y, InValue.X, 0.f);
	if (CanTurn(TargetRotation))
	{
		AddControllerYawInput(InValue.X);
		AddControllerPitchInput(InValue.Y);
	}
}

void AThirdPersonCharacter::AddZoom_Implementation(float InValue)
{
	if (CanZoom(SpringArmComponent->TargetArmLength + InValue))
	{
		SpringArmComponent->AddTargetArmLength(InValue);
	}
}

void AThirdPersonCharacter::SetLocation_Implementation(FVector InValue)
{
	if (CanMove(InValue))
	{
		SetActorLocation(InValue);
	}
}

void AThirdPersonCharacter::SetRotation_Implementation(FRotator InValue)
{
	if (CanTurn(InValue))
	{
		SetActorRotation(FRotator(0.f, InValue.Yaw, 0.f));
		SpringArmComponent->SetRelativeRotation(FRotator(InValue.Pitch, 0.f, 0.f), true);
	}
}

void AThirdPersonCharacter::SetZoom_Implementation(float InValue)
{
	if (CanZoom(InValue))
	{
		SpringArmComponent->SetTargetArmLength(InValue);
	}
}

FVector AThirdPersonCharacter::GetLocation()
{
	return GetActorLocation();
}

FRotator AThirdPersonCharacter::GetRotation()
{
	return GetActorRotation();
}

float AThirdPersonCharacter::GetZoom()
{
	return -1;
}
