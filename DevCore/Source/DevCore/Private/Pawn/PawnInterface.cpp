// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawn/PawnInterface.h"

IPawnInterface::IPawnInterface()
	: bLock(false),
	  bLockLocation(false),
	  bLockRotation(false)
{
}

void IPawnInterface::SetLockState(const bool InLock, const bool InLockLocation, const bool InLockRotation)
{
	bLock = InLock;
	bLockLocation = InLockLocation;
	bLockRotation = InLockRotation;
}

bool IPawnInterface::CanMove()
{
	return !bLock && !bLockLocation;
}

bool IPawnInterface::CanTurn()
{
	return !bLock && !bLockRotation;
}
