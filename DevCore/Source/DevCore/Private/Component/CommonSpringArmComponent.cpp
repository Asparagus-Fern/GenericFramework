// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CommonSpringArmComponent.h"

#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Debug/DebugType.h"
#include "Kismet/GameplayStatics.h"
#include "Pawn/PawnInterface.h"
#include "Pawn/PawnManagerSetting.h"
#include "PhysicsEngine/PhysicsSettings.h"

UCommonSpringArmComponent::UCommonSpringArmComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bDoCollisionTest = false;
	bEnableCameraLag = true;
	bEnableCameraRotationLag = true;

	TargetArmLength = 3000.f;
}

void UCommonSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();

	DesiredArmLength = TargetArmLength;
}

void UCommonSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateTargetArmLength(DeltaTime);
}

void UCommonSpringArmComponent::AddTargetArmLength(const float InValue)
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
	DesiredArmLength += (FMath::Abs(FMath::Sin(UE_DOUBLE_PI / (180.0) * Rotation.Pitch)) * PitchRate * TargetArmLength * UPawnManagerSetting::Get()->ZoomSpeed * InValue);
	DesiredArmLength = SpringArmLimit.GetLimitSpringArmLength(DesiredArmLength);
}

void UCommonSpringArmComponent::SetTargetArmLength(const float InValue)
{
	TargetArmLength = DesiredArmLength = InValue;
	UpdateDesiredArmLocation(false, false, false, 0.f);
}

void UCommonSpringArmComponent::UpdateTargetArmLength(float DeltaTime)
{
	TargetArmLength = TargetArmLength + DeltaTime * (DesiredArmLength - TargetArmLength);
}
