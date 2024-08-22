// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnType.h"

bool FPawnLockingState::CanMove(const FVector& CurrentLocation) const
{
	if (bFullyLock)
	{
		return false;
	}

	if (bLockLocation)
	{
		return false;
	}

	if
	(
		bLimitLocation &&
		(
			CurrentLocation.X < LimitMinLocation.X || CurrentLocation.Y < LimitMinLocation.Y || CurrentLocation.Z < LimitMinLocation.Z ||
			CurrentLocation.X > LimitMaxLocation.X || CurrentLocation.Y > LimitMaxLocation.Y || CurrentLocation.Z > LimitMaxLocation.Z
		)
	)
	{
		return false;
	}

	return true;
}

bool FPawnLockingState::CanTurn(const FRotator& CurrentRotation) const
{
	if (bFullyLock)
	{
		return false;
	}

	if (bLockRotation)
	{
		return false;
	}

	if
	(
		bLimitRotation &&
		(
			CurrentRotation.Pitch < LimitMinRotation.Pitch || CurrentRotation.Yaw < LimitMinRotation.Yaw || CurrentRotation.Roll < LimitMinRotation.Roll ||
			CurrentRotation.Pitch > LimitMaxRotation.Pitch || CurrentRotation.Yaw > LimitMaxRotation.Yaw || CurrentRotation.Roll > LimitMaxRotation.Roll
		)
	)
	{
		return false;
	}

	return true;
}

bool FPawnLockingState::CanZoom(const float CurrentSpringArmLength) const
{
	if (bFullyLock)
	{
		return false;
	}

	if (bLockSpringArmIfExist)
	{
		return false;
	}

	if (bLimitSpringArmIfExist && (CurrentSpringArmLength < LimitSpringArmLength.X || CurrentSpringArmLength > LimitSpringArmLength.Y))
	{
		return false;
	}

	return true;
}

void FPawnLockingState::UnLock()
{
	bFullyLock = false;
	bLockLocation = false;
	bLimitLocation = false;
	bLockRotation = false;
	bLimitRotation = false;
	bLockSpringArmIfExist = false;
	bLimitSpringArmIfExist = false;
}
