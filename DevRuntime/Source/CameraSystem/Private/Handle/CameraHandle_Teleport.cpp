// Fill out your copyright notice in the Description page of Project Settings.


#include "Handle/CameraHandle_Teleport.h"

UCameraHandle_Teleport::UCameraHandle_Teleport()
{
}

bool UCameraHandle_Teleport::HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint)
{
	if (Super::HandleSwitchToCameraPoint_Implementation(InPlayerController, InCameraPoint))
	{
		
	}
	
	return false;
}
