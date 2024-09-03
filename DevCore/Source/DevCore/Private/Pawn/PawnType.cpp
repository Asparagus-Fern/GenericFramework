// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnType.h"

bool FPawnLocationLimit::CanMove(const FVector& TargetLocation) const
{
	if (bLimitLocationX && (TargetLocation.X < LocationXRange.X || TargetLocation.X > LocationXRange.Y))
	{
		return false;
	}

	if (bLimitLocationY && (TargetLocation.Y < LocationYRange.X || TargetLocation.Y > LocationYRange.Y))
	{
		return false;
	}

	if (bLimitLocationZ && (TargetLocation.Z < LocationZRange.X || TargetLocation.Z > LocationZRange.Y))
	{
		return false;
	}

	return true;
}

FVector FPawnLocationLimit::GetLimitLocation(const FVector& TargetLocation) const
{
	FVector Result = TargetLocation;
	if (bLimitLocationX)
	{
		Result.X = FMath::Clamp(Result.X, LocationXRange.X, LocationXRange.Y);
	}

	if (bLimitLocationY)
	{
		Result.Y = FMath::Clamp(Result.Y, LocationYRange.X, LocationYRange.Y);
	}

	if (bLimitLocationZ)
	{
		Result.Z = FMath::Clamp(Result.Z, LocationZRange.X, LocationZRange.Y);
	}
	return Result;
}

void FPawnLocationLimit::UnLimit()
{
	bLimitLocationX = false;
	bLimitLocationY = false;
	bLimitLocationZ = false;
}

bool FPawnRotationLimit::CanTurn(const FRotator& TargetRotation) const
{
	if (bLimitPitch && (TargetRotation.Pitch < PitchRange.X || TargetRotation.Pitch > PitchRange.Y))
	{
		return false;
	}

	if (bLimitYaw && (TargetRotation.Yaw < PitchRange.X || TargetRotation.Yaw > PitchRange.Y))
	{
		return false;
	}

	return true;
}

FRotator FPawnRotationLimit::GetLimitRotation(const FRotator& TargetRotation) const
{
	FRotator Result = TargetRotation;

	if (Result.Roll != 0.f)
	{
		Result.Yaw += Result.Roll;
		Result.Roll = 0.f;
	}

	if (bLimitPitch)
	{
		Result.Pitch = FMath::Clamp(Result.Pitch, PitchRange.X, PitchRange.Y);
	}
	else if (Result.Pitch == -90.f)
	{
		Result.Pitch = -89.9f;
	}
	else if (Result.Pitch == 90.f)
	{
		Result.Pitch = 89.9f;
	}

	if (bLimitYaw)
	{
		Result.Yaw = FMath::Clamp(Result.Yaw, YawRange.X, YawRange.Y);
	}

	return Result;
}

void FPawnRotationLimit::UnLimit()
{
	bLimitPitch = false;
	bLimitYaw = false;
}

bool FSpringArmLimit::CanZoom(float TargetSpringArmLength) const
{
	if (bLimitSpringArmLength && (TargetSpringArmLength < SpringArmLengthRange.X || TargetSpringArmLength > SpringArmLengthRange.Y))
	{
		return false;
	}

	return true;
}

float FSpringArmLimit::GetLimitSpringArmLength(float TargetSpringArmLength) const
{
	if (bLimitSpringArmLength)
	{
		return FMath::Clamp(TargetSpringArmLength, SpringArmLengthRange.X > 0 ? SpringArmLengthRange.X : 0.01f, SpringArmLengthRange.Y);
	}
	else if (TargetSpringArmLength <= 0.f)
	{
		return 0.01f;
	}
	else
	{
		return TargetSpringArmLength;
	}
}

void FSpringArmLimit::UnLimit()
{
	bLimitSpringArmLength = false;
}

bool FPawnLockingState::CanMove(const FVector& TargetLocation) const
{
	if (bFullyLock)
	{
		return false;
	}

	if (bLockLocation)
	{
		return false;
	}

	return PawnLocationLimit.CanMove(TargetLocation);
}

bool FPawnLockingState::CanTurn(const FRotator& TargetRotation) const
{
	if (bFullyLock)
	{
		return false;
	}

	if (bLockRotation)
	{
		return false;
	}

	return PawnRotationLimit.CanTurn(TargetRotation);
}

bool FPawnLockingState::CanZoom(const float TargetSpringArmLength) const
{
	if (bFullyLock)
	{
		return false;
	}

	if (bLockSpringArm)
	{
		return false;
	}

	return SpringArmLimit.CanZoom(TargetSpringArmLength);
}

void FPawnLockingState::UnLock()
{
	bFullyLock = false;
	bLockLocation = false;
	bLockRotation = false;
	bLockSpringArm = false;
}

void FPawnLockingState::UnLimit()
{
	PawnLocationLimit.UnLimit();
	PawnRotationLimit.UnLimit();
	SpringArmLimit.UnLimit();
}
