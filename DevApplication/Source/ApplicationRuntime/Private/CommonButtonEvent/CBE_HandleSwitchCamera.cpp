// Fill out your copyright notice in the Description page of Project Settings.

#include "CommonButtonEvent/CBE_HandleSwitchCamera.h"

#include "CameraManager.h"
#include "CameraHandle/CameraHandle_Transition.h"
#include "Manager/ManagerGlobal.h"

UCBE_HandleSwitchCamera::UCBE_HandleSwitchCamera()
{
	bIsAsync = true;
	TargetCameraHandle = CreateDefaultSubobject<UCameraHandle_Transition>("CameraHandle");
}

bool UCBE_HandleSwitchCamera::CanExecuteButtonEvent_Implementation()
{
	return TargetCameraTag.IsValid() && IsValid(TargetCameraHandle);
}

void UCBE_HandleSwitchCamera::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	const auto OnSwitchFinish = FSimpleDelegate::CreateLambda([this]()
		{
			MarkAsActivedFinish();
		}
	);

	if (bIsAsync)
	{
		GetManager<UCameraManager>()->SwitchToCamera(TargetPlayerIndex, TargetCameraTag, TargetCameraHandle, OnSwitchFinish);
	}
	else
	{
		GetManager<UCameraManager>()->SwitchToCamera(TargetPlayerIndex, TargetCameraTag, TargetCameraHandle);
	}
}
