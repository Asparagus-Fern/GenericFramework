// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraHandle.h"

#include "CameraSystemType.h"

UCameraHandle::UCameraHandle()
{
	bLockCamera = false;
}

void UCameraHandle::HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPoint* InCameraPoint)
{
	OwnerPlayerController = InPlayerController;
	SwitchCameraPointHandle = InPlayerController->PlayerCameraManager->OnBlendComplete().AddUFunction(this, "OnSwitchToCameraPointFinish");
}

void UCameraHandle::OnSwitchToCameraPointFinish_Implementation()
{
	OnSwitchCameraFinish.Broadcast();
	FCameraSystemDelegates::OnSwitchCameraFinish.Broadcast();

	SwitchCameraPointHandle.Reset();
}
