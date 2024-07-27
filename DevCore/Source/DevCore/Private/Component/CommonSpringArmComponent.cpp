// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CommonSpringArmComponent.h"

#include "BPFunctions/BPFunctions_Gameplay.h"
#include "Debug/DebugType.h"
#include "Kismet/GameplayStatics.h"
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
	float ArmLengthWeight = 0.5f;

	const float Degree = FMath::GetMappedRangeValueClamped(FVector2D(MinArmLength, MaxArmLength), FVector2D(0.f, 90.f), TargetArmLength);
	float CosValue = FMath::Cos(UE_DOUBLE_PI / (180.0) * Degree);
	CosValue = FMath::GetMappedRangeValueClamped(FVector2D(0.f, 1.f), FVector2D(0.1f, 0.9f), CosValue);

	DesiredArmLength += (TargetArmLength / 10.f * CosValue * ArmZoomSpeedRate * InValue);
	if (DesiredArmLength <= 0)
	{
		FHitResult HitResult;
		if (UBPFunctions_Gameplay::GetActorDownHitResult(GetOwner(), HitResult))
		{
			DesiredArmLength += HitResult.Distance;
		}
	}

	DesiredArmLength = FMath::Clamp(DesiredArmLength, MinArmLength, MaxArmLength);
}

void UCommonSpringArmComponent::SetTargetArmLength(const float InValue)
{
	TargetArmLength = DesiredArmLength = FMath::Clamp(InValue, MinArmLength, MaxArmLength);
	UpdateDesiredArmLocation(false, false, false, 0.f);
}

void UCommonSpringArmComponent::UpdateTargetArmLength(float DeltaTime)
{
	TargetArmLength = TargetArmLength + DeltaTime * (DesiredArmLength - TargetArmLength);
}
