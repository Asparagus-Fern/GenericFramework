// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Camera.h"

#include "CameraManager.h"
#include "Manager/ManagerProxy.h"

ACameraPointBase* UBPFunctions_Camera::GetCameraPoint(const FGameplayTag InCameraTag)
{
	if (const UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		return CameraManager->GetCameraPoint(InCameraTag);
	}

	return nullptr;
}

void UBPFunctions_Camera::SwitchToCamera_Transform_HandleClass(int32 InPlayerIndex, FVector Location, FRotator Rotation, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, Location, Rotation, InCameraHandleClass);
	}
}

void UBPFunctions_Camera::SwitchToCamera_Transform_Handle(int32 InPlayerIndex, FVector Location, FRotator Rotation, UCameraHandle* InCameraHandle)
{
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, Location, Rotation, InCameraHandle);
	}
}

void UBPFunctions_Camera::SwitchToCamera_Actor_HandleClass(const int32 InPlayerIndex, ACameraActor* InCameraActor, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraActor, InCameraHandleClass);
	}
}

void UBPFunctions_Camera::SwitchToCamera_Actor_Handle(const int32 InPlayerIndex, ACameraActor* InCameraActor, UCameraHandle* InCameraHandle)
{
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraActor, InCameraHandle);
	}
}

void UBPFunctions_Camera::SwitchToCamera_Component_HandleClass(const int32 InPlayerIndex, UCameraComponent* InCameraComponent, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraComponent, InCameraHandleClass);
	}
}

void UBPFunctions_Camera::SwitchToCamera_Component_Handle(const int32 InPlayerIndex, UCameraComponent* InCameraComponent, UCameraHandle* InCameraHandle)
{
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraComponent, InCameraHandle);
	}
}

void UBPFunctions_Camera::SwitchToCamera_Tag_HandleClass(const int32 InPlayerIndex, const FGameplayTag InCameraTag, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraTag, InCameraHandleClass);
	}
}

void UBPFunctions_Camera::SwitchToCamera_Tag_Handle(const int32 InPlayerIndex, const FGameplayTag InCameraTag, UCameraHandle* InCameraHandle)
{
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraTag, InCameraHandle);
	}
}

void UBPFunctions_Camera::SwitchToCamera_CameraPoint_HandleClass(const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraPoint, InCameraHandleClass);
	}
}

void UBPFunctions_Camera::SwitchToCamera_CameraPoint_Handle(const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, UCameraHandle* InCameraHandle)
{
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraPoint, InCameraHandle);
	}
}

void UBPFunctions_Camera::SwitchToCurrent_HandleClass(const int32 InPlayerIndex, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCurrent(InPlayerIndex, InCameraHandleClass);
	}
}

void UBPFunctions_Camera::SwitchToCurrent_Handle(const int32 InPlayerIndex, UCameraHandle* InCameraHandle)
{
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCurrent(InPlayerIndex, InCameraHandle);
	}
}

void UBPFunctions_Camera::SwitchToPrevious_HandleClass(const int32 InPlayerIndex, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		CameraManager->SwitchToPrevious(InPlayerIndex, InCameraHandleClass);
	}
}

void UBPFunctions_Camera::SwitchToPrevious_Handle(const int32 InPlayerIndex, UCameraHandle* InCameraHandle)
{
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		CameraManager->SwitchToPrevious(InPlayerIndex, InCameraHandle);
	}
}
