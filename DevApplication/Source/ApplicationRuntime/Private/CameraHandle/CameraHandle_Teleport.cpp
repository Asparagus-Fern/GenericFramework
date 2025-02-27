// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraHandle/CameraHandle_Teleport.h"

UCameraHandle_Teleport::UCameraHandle_Teleport()
{
}

bool UCameraHandle_Teleport::HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint)
{
	if (Super::HandleSwitchToCameraPoint_Implementation(InPlayerController, InCameraPoint))
	{
		NativeOnSwitchToCameraPointFinish();
		return true;
	}

	return false;
}

void UCameraHandle_Teleport::OnSwitchToCameraPointFinish_Implementation()
{
	Super::OnSwitchToCameraPointFinish_Implementation();
}
