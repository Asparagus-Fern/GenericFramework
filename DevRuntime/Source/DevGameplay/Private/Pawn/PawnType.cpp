// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnType.h"

bool FPawnLocationLimit::CanMove(const FVector& TargetLocation) const
{
	TRange<double> Range;

	{
		Range = TRange<double>::Exclusive(LocationXRange.X, LocationXRange.Y);
		if (bLimitLocationX && !Range.Contains(TargetLocation.X))
		{
			return false;
		}
	}

	{
		Range = TRange<double>::Exclusive(LocationYRange.X, LocationYRange.Y);
		if (bLimitLocationY && !Range.Contains(TargetLocation.Y))
		{
			return false;
		}
	}

	{
		Range = TRange<double>::Exclusive(LocationZRange.X, LocationZRange.Y);
		if (bLimitLocationZ && !Range.Contains(TargetLocation.Z))
		{
			return false;
		}
	}

	return true;
}

bool FPawnRotationLimit::CanTurn(const FRotator& TargetRotation) const
{
	TRange<double> Range;

	{
		Range = TRange<double>::Exclusive(PitchRange.X, PitchRange.Y);
		if (bLimitPitch && !Range.Contains(TargetRotation.Pitch))
		{
			return false;
		}
	}

	{
		Range = TRange<double>::Exclusive(YawRange.X, YawRange.Y);
		if (bLimitYaw && !Range.Contains(TargetRotation.Yaw))
		{
			return false;
		}
	}

	{
		Range = TRange<double>::Exclusive(RollRange.X, RollRange.Y);
		if (bLimitYaw && !Range.Contains(TargetRotation.Roll))
		{
			return false;
		}
	}

	return true;
}

bool FSpringArmLimit::CanZoom(float TargetSpringArmLength) const
{
	const TRange<double> Range = TRange<double>::Exclusive(SpringArmLengthRange.X, SpringArmLengthRange.Y);
	if (bLimitSpringArmLength && !Range.Contains(TargetSpringArmLength))
	{
		return false;
	}

	return true;
}
