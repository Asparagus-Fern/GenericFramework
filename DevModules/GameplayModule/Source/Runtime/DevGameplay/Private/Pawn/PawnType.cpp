// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Pawn/PawnType.h"

bool FPawnLocationLimit::CanMove(const FVector& TargetLocation) const
{
	if (bLimitLocationX && (TargetLocation.X <= LocationXRange.X || TargetLocation.X >= LocationXRange.Y))
	{
		return false;
	}

	if (bLimitLocationY && (TargetLocation.Y <= LocationYRange.X || TargetLocation.Y >= LocationYRange.Y))
	{
		return false;
	}

	if (bLimitLocationZ && (TargetLocation.Z <= LocationZRange.X || TargetLocation.Z >= LocationZRange.Y))
	{
		return false;
	}

	return true;
}

bool FPawnRotationLimit::CanTurn(const FRotator& TargetRotation) const
{
	if (bLimitPitch && (TargetRotation.Pitch <= PitchRange.X || TargetRotation.Pitch >= PitchRange.Y))
	{
		return false;
	}

	if (bLimitYaw && (TargetRotation.Yaw <= YawRange.X || TargetRotation.Yaw >= YawRange.Y))
	{
		return false;
	}

	if (bLimitRoll && (TargetRotation.Roll <= RollRange.X || TargetRotation.Roll >= RollRange.Y))
	{
		return false;
	}

	return true;
}

bool FSpringArmLimit::CanZoom(float TargetSpringArmLength) const
{
	if (bLimitSpringArmLength && (TargetSpringArmLength <= SpringArmLengthRange.X || TargetSpringArmLength >= SpringArmLengthRange.Y))
	{
		return false;
	}

	return true;
}
