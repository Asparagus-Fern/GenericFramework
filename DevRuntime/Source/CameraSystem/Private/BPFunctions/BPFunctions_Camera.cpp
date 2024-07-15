// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Camera.h"

#include "CameraManager.h"
#include "Handle/CameraHandle.h"
#include "Manager/ManagerGlobal.h"

void UBPFunctions_Camera::AddCameraPoint(const FGameplayTag InCameraTag, ACameraPointBase* InCameraPoint)
{
	GetManager<UCameraManager>()->AddCameraPoint(InCameraTag, InCameraPoint);
}

void UBPFunctions_Camera::RemoveCameraPoint(const FGameplayTag InCameraTag)
{
	GetManager<UCameraManager>()->RemoveCameraPoint(InCameraTag);
}

ACameraPointBase* UBPFunctions_Camera::GetCameraPoint(const FGameplayTag InCameraTag)
{
	return GetManager<UCameraManager>()->GetCameraPoint(InCameraTag);
}

bool UBPFunctions_Camera::CanSwitchToCamera(const FGameplayTag InCameraTag)
{
	return GetManager<UCameraManager>()->CanSwitchToCamera(InCameraTag);
}

void UBPFunctions_Camera::SwitchToCameraByHandle(FGameplayTag InCameraTag, TSubclassOf<UCameraHandle> SwitchCameraHandleClass)
{
	SwitchToCamera(InCameraTag, NewObject<UCameraHandle>(GetManager<UCameraManager>(), SwitchCameraHandleClass));
}

void UBPFunctions_Camera::SwitchToCamera(const FGameplayTag InCameraTag, UCameraHandle* SwitchCameraHandle)
{
	GetManager<UCameraManager>()->SwitchToCamera(InCameraTag, SwitchCameraHandle);
}

void UBPFunctions_Camera::SwitchToCameraByPlayerController(APlayerController* PlayerController, FGameplayTag InCameraTag, UCameraHandle* SwitchCameraHandle)
{
	GetManager<UCameraManager>()->SwitchToCamera(PlayerController, InCameraTag, SwitchCameraHandle);
}
