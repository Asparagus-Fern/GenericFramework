// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DevCharacter.h"

#include "AIController.h"
#include "EnhancedInputComponent.h"
#include "Input/CommonInputComponent.h"
#include "Input/InputHandleComponent.h"
#include "Kismet/KismetMathLibrary.h"

ADevCharacter::FCharacterDelegate ADevCharacter::OnCharacterRegister;
ADevCharacter::FCharacterDelegate ADevCharacter::OnCharacterUnRegister;

ADevCharacter::ADevCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterName = "DevCharacter";
	InputHandleComponent = CreateDefaultSubobject<UInputHandleComponent>("InputHandle");
}

void ADevCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnCharacterRegister.Broadcast(this);
}

void ADevCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnCharacterUnRegister.Broadcast(this);
	Super::EndPlay(EndPlayReason);
}

void ADevCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UCommonInputComponent* CommonInputComponent = CastChecked<UCommonInputComponent>(PlayerInputComponent))
	{
		CommonInputComponent->RegisterInputHandle(InputHandleComponent);
	}
}

void ADevCharacter::AddLocation_Implementation(FVector2D InValue)
{
	AddMovementInput(UKismetMathLibrary::GetRightVector(FRotator(0.f, GetControlRotation().Yaw, GetControlRotation().Roll)), InValue.X);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(FRotator(0.f, GetControlRotation().Yaw, 0.f)), InValue.Y);
}

void ADevCharacter::AddRotation_Implementation(FVector2D InValue)
{
	AddControllerYawInput(InValue.X);
	AddControllerPitchInput(InValue.Y);
}

void ADevCharacter::AddZoom_Implementation(float InValue)
{
}

void ADevCharacter::SetLocation_Implementation(FVector InValue)
{
	SetActorLocation(InValue);
}

void ADevCharacter::SetRotation_Implementation(FRotator InValue)
{
	SetActorRotation(InValue);
}

void ADevCharacter::SetZoom_Implementation(float InValue)
{
}

FVector ADevCharacter::GetLocation_Implementation()
{
	return GetActorLocation();
}

FRotator ADevCharacter::GetRotation_Implementation()
{
	return GetActorRotation();
}

float ADevCharacter::GetZoom_Implementation()
{
	return -1.f;
}

bool ADevCharacter::IsPlayer_Implementation()
{
	return IsValid(Cast<APlayerController>(GetController()));
}

bool ADevCharacter::IsAI_Implementation()
{
	return IsValid(Cast<AAIController>(GetController()));
}

APlayerController* ADevCharacter::GetPlayerController_Implementation()
{
	return Cast<APlayerController>(GetController());
}

AAIController* ADevCharacter::GetAIController_Implementation()
{
	return Cast<AAIController>(GetController());
}
