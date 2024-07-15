// Fill out your copyright notice in the Description page of Project Settings.

#include "Handle/CameraHandle.h"

#include "CameraSystemType.h"
#include "CameraPoint/CameraPointBase.h"

UCameraHandle::UCameraHandle()
{
	bLock = false;
	bLockLocation = false;
	bLockRotation = false;
}

bool UCameraHandle::HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint)
{
	if (IsValid(InPlayerController) && IsValid(InCameraPoint))
	{
		OwnerPlayerController = InPlayerController;
		TargetCameraPoint = InCameraPoint;

		return true;
	}

	return false;
}

void UCameraHandle::OnSwitchToCameraPointFinish()
{
	SwitchCameraPointHandle.Reset();
	FCameraSystemDelegates::OnSwitchCameraFinish.Broadcast(this);
	OnSwitchCameraFinish.Broadcast();
}
