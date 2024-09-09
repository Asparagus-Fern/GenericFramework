// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/SwitchToCameraAsyncAction.h"

#include "CameraManager.h"
#include "Manager/ManagerGlobal.h"

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Transform_HandleClass(const int32 InPlayerIndex, const FVector Location, const FRotator Rotation, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, Location, Rotation, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Transform_Handle(const int32 InPlayerIndex, const FVector Location, const FRotator Rotation, UCameraHandle* InCameraHandle)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, Location, Rotation, InCameraHandle, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Actor_HandleClass(const int32 InPlayerIndex, ACameraActor* InCameraActor, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraActor, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Actor_Handle(const int32 InPlayerIndex, ACameraActor* InCameraActor, UCameraHandle* InCameraHandle)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraActor, InCameraHandle, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Component_HandleClass(const int32 InPlayerIndex, UCameraComponent* InCameraComponent, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraComponent, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Component_Handle(const int32 InPlayerIndex, UCameraComponent* InCameraComponent, UCameraHandle* InCameraHandle)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraComponent, InCameraHandle, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Tag_HandleClass(const int32 InPlayerIndex, const FGameplayTag InCameraTag, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraTag, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_Tag_Handle(const int32 InPlayerIndex, const FGameplayTag InCameraTag, UCameraHandle* InCameraHandle)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraTag, InCameraHandle, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_CameraPoint_HandleClass(const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, const TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraPoint, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCamera_CameraPoint_Handle(const int32 InPlayerIndex, ACameraPointBase* InCameraPoint, UCameraHandle* InCameraHandle)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCamera(InPlayerIndex, InCameraPoint, InCameraHandle, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCurrent_HandleClass(int32 InPlayerIndex, TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCurrent(InPlayerIndex, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToCurrent_Handle(int32 InPlayerIndex, UCameraHandle* InCameraHandle)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		CameraManager->SwitchToCurrent(InPlayerIndex, InCameraHandle, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToPrevious_HandleClass(int32 InPlayerIndex, TSubclassOf<UCameraHandle> InCameraHandleClass)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		CameraManager->SwitchToPrevious(InPlayerIndex, InCameraHandleClass, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

USwitchToCameraAsyncAction* USwitchToCameraAsyncAction::SwitchToPrevious_Handle(int32 InPlayerIndex, UCameraHandle* InCameraHandle)
{
	USwitchToCameraAsyncAction* NewAction = NewObject<USwitchToCameraAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		CameraManager->SwitchToPrevious(InPlayerIndex, InCameraHandle, FSimpleDelegate::CreateUObject(NewAction, &USwitchToCameraAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

void USwitchToCameraAsyncAction::OnHandleFinish()
{
	OnFinish.Broadcast();
}
