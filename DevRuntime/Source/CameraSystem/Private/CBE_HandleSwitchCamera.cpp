// Fill out your copyright notice in the Description page of Project Settings.


#include "CBE_HandleSwitchCamera.h"

#include "CameraManager.h"
#include "CameraSystemType.h"
#include "Manager/ManagerGlobal.h"

void UCBE_HandleSwitchCamera::NativeOnActived()
{
	Super::NativeOnActived();

	if (CameraTag.IsValid())
	{
		SwitchCameraFinishHandle = FCameraSystemDelegates::OnSwitchCameraFinish.AddUObject(this, &UCBE_HandleSwitchCamera::OnSwitchCameraFinish);
		GetManager<UCameraManager>()->SwitchToCamera(CameraTag);
	}
}

void UCBE_HandleSwitchCamera::NativeOnInactived()
{
	Super::NativeOnInactived();
	RequestInactivateFinish();
}

void UCBE_HandleSwitchCamera::OnSwitchCameraFinish(UCameraHandle* InCameraHandle)
{
	SwitchCameraFinishHandle.Reset();
	RequestActivateFinish();
}
