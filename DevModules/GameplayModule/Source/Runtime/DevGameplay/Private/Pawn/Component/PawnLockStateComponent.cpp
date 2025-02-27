// Fill out your copyright notice in the Description page of Project Settings.

#include "Pawn/Component/PawnLockStateComponent.h"

#include "Pawn/PawnType.h"

UPawnLockStateComponent::UPawnLockStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPawnLockStateComponent::BeginPlay()
{
	Super::BeginPlay();
}

IPawnLockStateInterface::IPawnLockStateInterface()
{
}

FPawnLockState UPawnLockStateComponent::GetPawnLockState()
{
	return PawnLockState;
}

bool UPawnLockStateComponent::CanMove(const FVector& TargetLocation) const
{
	if (PawnLockState.bFullyLock)
	{
		return false;
	}

	if (PawnLockState.bLockLocation)
	{
		return false;
	}

	return PawnLockState.PawnLocationLimit.CanMove(TargetLocation);
}

bool UPawnLockStateComponent::CanTurn(const FRotator& TargetRotation) const
{
	if (PawnLockState.bFullyLock)
	{
		return false;
	}

	if (PawnLockState.bLockRotation)
	{
		return false;
	}

	return PawnLockState.PawnRotationLimit.CanTurn(TargetRotation);
}

bool UPawnLockStateComponent::CanZoom(float TargetSpringArmLength) const
{
	if (PawnLockState.bFullyLock)
	{
		return false;
	}

	if (PawnLockState.bLockSpringArm)
	{
		return false;
	}

	return PawnLockState.SpringArmLimit.CanZoom(TargetSpringArmLength);
}

FVector UPawnLockStateComponent::GetLimitLocation(const FVector& TargetLocation) const
{
	const FPawnLocationLimit PawnRotationLimit = PawnLockState.PawnLocationLimit;
	FVector Result = TargetLocation;

	if (PawnRotationLimit.bLimitLocationX)
	{
		Result.X = FMath::Clamp(Result.X, PawnRotationLimit.LocationXRange.X, PawnRotationLimit.LocationXRange.Y);
	}

	if (PawnRotationLimit.bLimitLocationY)
	{
		Result.Y = FMath::Clamp(Result.Y, PawnRotationLimit.LocationYRange.X, PawnRotationLimit.LocationYRange.Y);
	}

	if (PawnRotationLimit.bLimitLocationZ)
	{
		Result.Z = FMath::Clamp(Result.Z, PawnRotationLimit.LocationZRange.X, PawnRotationLimit.LocationZRange.Y);
	}

	return Result;
}

FRotator UPawnLockStateComponent::GetLimitRotation(const FRotator& TargetRotation) const
{
	const FPawnRotationLimit PawnRotationLimit = PawnLockState.PawnRotationLimit;
	FRotator Result = TargetRotation;

	if (PawnRotationLimit.bLimitPitch)
	{
		Result.Pitch = FMath::Clamp(Result.Pitch, PawnRotationLimit.PitchRange.X, PawnRotationLimit.PitchRange.Y);
	}

	if (PawnRotationLimit.bLimitPitch)
	{
		Result.Yaw = FMath::Clamp(Result.Yaw, PawnRotationLimit.YawRange.X, PawnRotationLimit.YawRange.Y);
	}

	if (PawnRotationLimit.bLimitRoll)
	{
		Result.Roll = FMath::Clamp(Result.Roll, PawnRotationLimit.RollRange.X, PawnRotationLimit.RollRange.Y);
	}

	return Result;
}

float UPawnLockStateComponent::GetLimitSpringArmLength(float TargetSpringArmLength) const
{
	const FSpringArmLimit SpringArmLimit = PawnLockState.SpringArmLimit;

	if (SpringArmLimit.bLimitSpringArmLength)
	{
		return FMath::Clamp(TargetSpringArmLength, SpringArmLimit.SpringArmLengthRange.X, SpringArmLimit.SpringArmLengthRange.Y);
	}

	return TargetSpringArmLength;
}

void UPawnLockStateComponent::SetPawnLockState_Implementation(const FPawnLockState& InPawnLockState)
{
	PawnLockState = InPawnLockState;
}

void UPawnLockStateComponent::SetIsFullyLock_Implementation(bool InFullyLock)
{
	PawnLockState.bFullyLock = InFullyLock;
}

void UPawnLockStateComponent::SetIsLockLocation_Implementation(bool InLockLocation)
{
	PawnLockState.bLockLocation = InLockLocation;
}

void UPawnLockStateComponent::SetIsLockRotation_Implementation(bool InLockRotation)
{
	PawnLockState.bLockRotation = InLockRotation;
}

void UPawnLockStateComponent::SetIsLockSpringArm_Implementation(bool InLockSpringArm)
{
	PawnLockState.bLockSpringArm = InLockSpringArm;
}
