// Fill out your copyright notice in the Description page of Project Settings.


#include "CBE_HandleSwitchCamera.h"

#include "CameraManager.h"
#include "CameraSystemType.h"
#include "Manager/ManagerGlobal.h"

void UCBE_HandleSwitchCamera::NativeOnActived()
{
	Super::NativeOnActived();

	if (ActiveSwitchCameraTag.IsValid())
	{
		SwitchCameraFinishHandle = FCameraSystemDelegates::OnSwitchCameraFinish.AddUObject(this, &UCBE_HandleSwitchCamera::OnActiveSwitchCameraFinish);
		GetManager<UCameraManager>()->SwitchToCamera(ActiveSwitchCameraTag);
	}
	else
	{
		RequestActivateFinish();
	}
}

void UCBE_HandleSwitchCamera::NativeOnInactived()
{
	Super::NativeOnInactived();

	if (InactiveSwitchCameraTag.IsValid())
	{
		SwitchCameraFinishHandle = FCameraSystemDelegates::OnSwitchCameraFinish.AddUObject(this, &UCBE_HandleSwitchCamera::OnInactiveSwitchCameraFinish);
		GetManager<UCameraManager>()->SwitchToCamera(InactiveSwitchCameraTag);
	}
	else
	{
		RequestInactivateFinish();
	}
}

void UCBE_HandleSwitchCamera::OnActiveSwitchCameraFinish(UCameraHandle* InCameraHandle)
{
	SwitchCameraFinishHandle.Reset();
	RequestActivateFinish();
}

void UCBE_HandleSwitchCamera::OnInactiveSwitchCameraFinish(UCameraHandle* InCameraHandle)
{
	SwitchCameraFinishHandle.Reset();
	RequestInactivateFinish();
}
