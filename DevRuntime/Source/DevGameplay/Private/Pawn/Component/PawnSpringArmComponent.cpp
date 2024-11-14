// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/Component/PawnSpringArmComponent.h"

#include "Pawn/Component/PawnInputMovementComponent.h"
#include "Pawn/Component/PawnLockStateComponent.h"


UPawnSpringArmComponent::UPawnSpringArmComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bDoCollisionTest = false;
	bEnableCameraLag = true;
	bEnableCameraRotationLag = true;

	TargetArmLength = 3000.f;
}

void UPawnSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();

	DesiredArmLength = TargetArmLength;
}

void UPawnSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateTargetArmLength(DeltaTime);
}

void UPawnSpringArmComponent::AddTargetArmLength(const float InValue)
{
	float ZoomSpeedRate = 1.f;
	FRotator Rotation = GetRelativeRotation();

	if (GetOwner()->GetClass()->ImplementsInterface(UPawnInputMovementInterface::StaticClass()))
	{
		ZoomSpeedRate = IPawnInputMovementInterface::Execute_GetZoomSpeedRate(GetOwner());
		Rotation = IPawnInputMovementInterface::Execute_GetRotation(GetOwner());
	}

	const float PitchRate = FMath::GetMappedRangeValueClamped(FVector2D(0.f, 90.f), FVector2D(0.8f, 1.2f), FMath::Abs(Rotation.Pitch));
	DesiredArmLength += (FMath::Abs(FMath::Sin(UE_DOUBLE_PI / (180.0) * Rotation.Pitch)) * PitchRate * (TargetArmLength * 0.2f) * ZoomSpeedRate * InValue);

	if (GetOwner()->GetClass()->ImplementsInterface(UPawnLockStateInterface::StaticClass()))
	{
		DesiredArmLength = IPawnLockStateInterface::Execute_GetLimitSpringArmLength(GetOwner(), DesiredArmLength);
	}
}

void UPawnSpringArmComponent::SetTargetArmLength(const float InValue)
{
	TargetArmLength = DesiredArmLength = InValue;
	UpdateDesiredArmLocation(false, false, false, 0.f);
}

bool UPawnSpringArmComponent::GetIsReassessment(float InValue) const
{
	return DesiredArmLength + InValue < ReassessmentSpringArmLength;
}

void UPawnSpringArmComponent::UpdateTargetArmLength(float DeltaTime)
{
	TargetArmLength = TargetArmLength + (DeltaTime * SpringArmLag) * (DesiredArmLength - TargetArmLength);
}
