// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/SetCameraInputIdleAsyncAction.h"

#include "CameraManager.h"

USetCameraInputIdleAsyncAction* USetCameraInputIdleAsyncAction::SetCameraInputIdle(UCameraInputIdle* InCameraInputIdle)
{
	USetCameraInputIdleAsyncAction* NewAction = NewObject<USetCameraInputIdleAsyncAction>();

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		UCameraManager::OnCameraInputIdleReset.AddUObject(NewAction, &USetCameraInputIdleAsyncAction::CameraInputIdleReset);
		UCameraManager::OnCameraAutoSwitchStart.AddUObject(NewAction, &USetCameraInputIdleAsyncAction::CameraAutoSwitchStart);
		UCameraManager::OnCameraAutoSwitchStop.AddUObject(NewAction, &USetCameraInputIdleAsyncAction::CameraAutoSwitchStop);
		UCameraManager::OnCameraLensMovementStart.AddUObject(NewAction, &USetCameraInputIdleAsyncAction::CameraLensMovementStart);
		UCameraManager::OnCameraLensMovementStop.AddUObject(NewAction, &USetCameraInputIdleAsyncAction::CameraLensMovementStop);
		CameraManager->SetCameraInputIdle(InCameraInputIdle);
	}

	return NewAction;
}

void USetCameraInputIdleAsyncAction::CameraInputIdleReset(UCameraInputIdle* CameraInputIdle)
{
	UCameraManager::OnCameraAutoSwitchStart.RemoveAll(this);
	UCameraManager::OnCameraAutoSwitchStop.RemoveAll(this);
	UCameraManager::OnCameraInputIdleReset.RemoveAll(this);
	OnCameraAutoSwitchReset.Broadcast(CameraInputIdle);
}

void USetCameraInputIdleAsyncAction::CameraAutoSwitchStart(UCameraInputIdle* CameraInputIdle)
{
	OnCameraAutoSwitchStart.Broadcast(CameraInputIdle);
}

void USetCameraInputIdleAsyncAction::CameraAutoSwitchStop(UCameraInputIdle* CameraInputIdle)
{
	OnCameraAutoSwitchStop.Broadcast(CameraInputIdle);
}

void USetCameraInputIdleAsyncAction::CameraLensMovementStart(UCameraInputIdle* CameraInputIdle)
{
	OnCameraLensMovementStart.Broadcast(CameraInputIdle);
}

void USetCameraInputIdleAsyncAction::CameraLensMovementStop(UCameraInputIdle* CameraInputIdle)
{
	OnCameraLensMovementStop.Broadcast(CameraInputIdle);
}
