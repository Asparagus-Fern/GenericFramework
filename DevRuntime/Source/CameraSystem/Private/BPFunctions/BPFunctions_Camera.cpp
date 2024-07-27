// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Camera.h"

#include "CameraManager.h"
#include "Handle/CameraHandle.h"
#include "Manager/ManagerGlobal.h"

ACameraPointBase* UBPFunctions_Camera::GetCameraPoint(const FGameplayTag InCameraTag)
{
	return GetManager<UCameraManager>()->GetCameraPoint(InCameraTag);
}

bool UBPFunctions_Camera::CanSwitchToCamera(const FGameplayTag InCameraTag)
{
	return GetManager<UCameraManager>()->CanSwitchToCamera(InCameraTag);
}

void UBPFunctions_Camera::SwitchToCameraByComponentClass(UCameraComponent* InComponent, TSubclassOf<UCameraHandle> SwitchCameraHandleClass)
{
	GetManager<UCameraManager>()->SwitchToCamera(InComponent, NewObject<UCameraHandle>(GetManager<UCameraManager>(), SwitchCameraHandleClass));
}

void UBPFunctions_Camera::SwitchToCameraByComponent(UCameraComponent* InComponent, UCameraHandle* SwitchCameraHandle)
{
	GetManager<UCameraManager>()->SwitchToCamera(InComponent, SwitchCameraHandle);
}

void UBPFunctions_Camera::SwitchToCameraByHandleClass(FGameplayTag InCameraTag, TSubclassOf<UCameraHandle> SwitchCameraHandleClass)
{
	GetManager<UCameraManager>()->SwitchToCamera(InCameraTag, SwitchCameraHandleClass);
}

void UBPFunctions_Camera::SwitchToCameraByHandle(const FGameplayTag InCameraTag, UCameraHandle* SwitchCameraHandle)
{
	GetManager<UCameraManager>()->SwitchToCamera(InCameraTag, SwitchCameraHandle);
}