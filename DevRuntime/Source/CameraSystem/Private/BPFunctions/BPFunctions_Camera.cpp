// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Camera.h"

#include "CameraHandle.h"
#include "CameraManager.h"
#include "Manager/ManagerGlobal.h"

ACameraPointBase* UBPFunctions_Camera::GetCameraPoint(const UObject* WorldContextObject, const FGameplayTag InCameraTag)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (const UCameraManager* CameraManager = GetManager<UCameraManager>(World))
		{
			return CameraManager->GetCameraPoint(InCameraTag);
		}
	}

	return nullptr;
}

void UBPFunctions_Camera::SwitchToCamera_Transform_HandleClass(const UObject* WorldContextObject, int32 InPlayerIndex, FVector Location, FRotator Rotation, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UCameraManager* CameraManager = GetManager<UCameraManager>(World))
		{
			CameraManager->SwitchToCamera(InPlayerIndex, Location, Rotation, InCameraHandleClass);
		}
	}
}

void UBPFunctions_Camera::SwitchToCamera_Transform_Handle(const UObject* WorldContextObject, int32 InPlayerIndex, FVector Location, FRotator Rotation, UCameraHandle* InCameraHandle)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UCameraManager* CameraManager = GetManager<UCameraManager>(World))
		{
			CameraManager->SwitchToCamera(InPlayerIndex, Location, Rotation, InCameraHandle);
		}
	}
}

void UBPFunctions_Camera::SwitchToCamera_Actor_HandleClass(const UObject* WorldContextObject, const int32 InPlayerIndex, ACameraActor* InCameraActor, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UCameraManager* CameraManager = GetManager<UCameraManager>(World))
		{
			CameraManager->SwitchToCamera(InPlayerIndex, InCameraActor, InCameraHandleClass);
		}
	}
}

void UBPFunctions_Camera::SwitchToCamera_Actor_Handle(const UObject* WorldContextObject, const int32 InPlayerIndex, ACameraActor* InCameraActor, UCameraHandle* InCameraHandle)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UCameraManager* CameraManager = GetManager<UCameraManager>(World))
		{
			CameraManager->SwitchToCamera(InPlayerIndex, InCameraActor, InCameraHandle);
		}
	}
}

void UBPFunctions_Camera::SwitchToCamera_Component_HandleClass(const UObject* WorldContextObject, const int32 InPlayerIndex, UCameraComponent* InCameraComponent, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UCameraManager* CameraManager = GetManager<UCameraManager>(World))
		{
			CameraManager->SwitchToCamera(InPlayerIndex, InCameraComponent, InCameraHandleClass);
		}
	}
}

void UBPFunctions_Camera::SwitchToCamera_Component_Handle(const UObject* WorldContextObject, const int32 InPlayerIndex, UCameraComponent* InCameraComponent, UCameraHandle* InCameraHandle)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UCameraManager* CameraManager = GetManager<UCameraManager>(World))
		{
			CameraManager->SwitchToCamera(InPlayerIndex, InCameraComponent, InCameraHandle);
		}
	}
}

void UBPFunctions_Camera::SwitchToCamera_Tag_HandleClass(const UObject* WorldContextObject, const int32 InPlayerIndex, const FGameplayTag InCameraTag, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UCameraManager* CameraManager = GetManager<UCameraManager>(World))
		{
			CameraManager->SwitchToCamera(InPlayerIndex, InCameraTag, InCameraHandleClass);
		}
	}
}

void UBPFunctions_Camera::SwitchToCamera_Tag_Handle(const UObject* WorldContextObject, const int32 InPlayerIndex, const FGameplayTag InCameraTag, UCameraHandle* InCameraHandle)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UCameraManager* CameraManager = GetManager<UCameraManager>(World))
		{
			CameraManager->SwitchToCamera(InPlayerIndex, InCameraTag, InCameraHandle);
		}
	}
}

void UBPFunctions_Camera::SwitchToCamera_CameraPoint_HandleClass(const UObject* WorldContextObject, const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UCameraManager* CameraManager = GetManager<UCameraManager>(World))
		{
			CameraManager->SwitchToCamera(InPlayerIndex, InCameraPoint, InCameraHandleClass);
		}
	}
}

void UBPFunctions_Camera::SwitchToCamera_CameraPoint_Handle(const UObject* WorldContextObject, const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, UCameraHandle* InCameraHandle)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UCameraManager* CameraManager = GetManager<UCameraManager>(World))
		{
			CameraManager->SwitchToCamera(InPlayerIndex, InCameraPoint, InCameraHandle);
		}
	}
}
