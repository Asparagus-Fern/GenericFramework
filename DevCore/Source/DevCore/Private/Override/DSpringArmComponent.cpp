// Fill out your copyright notice in the Description page of Project Settings.

#include "Override/DSpringArmComponent.h"

#include "Pawn/PawnInterface.h"
#include "Pawn/PawnManagerSetting.h"

UDSpringArmComponent::UDSpringArmComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bDoCollisionTest = false;
	bEnableCameraLag = true;
	bEnableCameraRotationLag = true;

	TargetArmLength = 3000.f;
}

void UDSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();

	DesiredArmLength = TargetArmLength;
}

void UDSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateTargetArmLength(DeltaTime);
}

void UDSpringArmComponent::AddTargetArmLength(const float InValue)
{
	FRotator Rotation;
	if (GetOwner()->GetClass()->ImplementsInterface(UPawnInterface::StaticClass()))
	{
		Rotation = IPawnInterface::Execute_GetRotation(GetOwner());
	}
	else
	{
		Rotation = GetRelativeRotation();
	}

	const float PitchRate = FMath::GetMappedRangeValueClamped(FVector2D(0.f, 90.f), FVector2D(0.8f, 1.2f), FMath::Abs(Rotation.Pitch));
	DesiredArmLength += (FMath::Abs(FMath::Sin(UE_DOUBLE_PI / (180.0) * Rotation.Pitch)) * PitchRate * TargetArmLength * 0.75f * UPawnManagerSetting::Get()->ZoomSpeed * InValue);
	DesiredArmLength = SpringArmLimit.GetLimitSpringArmLength(DesiredArmLength);
}

void UDSpringArmComponent::SetTargetArmLength(const float InValue)
{
	TargetArmLength = DesiredArmLength = InValue;
	UpdateDesiredArmLocation(false, false, false, 0.f);
}

void UDSpringArmComponent::UpdateTargetArmLength(float DeltaTime)
{
	TargetArmLength = TargetArmLength + DeltaTime * (DesiredArmLength - TargetArmLength);
}
