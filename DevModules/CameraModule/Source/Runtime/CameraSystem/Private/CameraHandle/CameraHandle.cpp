// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraHandle/CameraHandle.h"

#include "CameraManager.h"
#include "CameraManagerSetting.h"
#include "CameraPoint/CameraPointBase.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ManagerProxy.h"

UCameraHandle::FCameraHandleDelegate UCameraHandle::OnSwitchCameraBegin;
UCameraHandle::FCameraHandleDelegate UCameraHandle::OnSwitchCameraFinish;

UWorld* UCameraHandle::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(), TEXT("CommonButtonEvent: %s has a null OuterPrivate in UCommonButtonEvent::GetWorld()"), *GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		if (const UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
		{
			return CameraManager->GetWorld();
		}
		else
		{
			return GetOuter()->GetWorld();
		}
	}
	return nullptr;
}

void UCameraHandle::Reset()
{
	NativeOnSwitchToCameraPointReset();
}

bool UCameraHandle::HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint)
{
	return true;
}

bool UCameraHandle::NativeHandleSwitchToCameraPoint(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint, FSimpleDelegate OnFinish)
{
	if (IsValid(InPlayerController) && IsValid(InCameraPoint))
	{
		OwnerPlayerController = InPlayerController;
		TargetCameraPoint = InCameraPoint;
		OnHandleFinish = OnFinish;

		OnSwitchCameraBegin.Broadcast(this);

		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsWithInterface(this, UCameraHandleInterface::StaticClass(), Actors);
		for (const auto Actor : Actors)
		{
			ICameraHandleInterface::Execute_HandleSwitchToCameraBegin(Actor, this);
		}

		return HandleSwitchToCameraPoint(InPlayerController, InCameraPoint);
	}

	OnFinish.ExecuteIfBound();
	return false;
}

void UCameraHandle::OnSwitchToCameraPointReset_Implementation()
{
	NativeOnSwitchToCameraPointFinish();
}

void UCameraHandle::NativeOnSwitchToCameraPointReset()
{
	OnSwitchToCameraPointReset();
}

void UCameraHandle::OnSwitchToCameraPointFinish_Implementation()
{
}

void UCameraHandle::NativeOnSwitchToCameraPointFinish()
{
	OnSwitchToCameraPointFinish();

	OnHandleFinish.ExecuteIfBound();
	OnSwitchCameraFinish.Broadcast(this);

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(this, UCameraHandleInterface::StaticClass(), Actors);
	for (const auto Actor : Actors)
	{
		ICameraHandleInterface::Execute_HandleSwitchToCameraFinish(Actor, this);
	}

	if (!TargetCameraPoint->CameraTag.IsValid() && UCameraManagerSetting::Get()->bDestroyEmptyCameraPointAfterSwitchFinish)
	{
		TargetCameraPoint->Destroy();
	}
	OwnerPlayerController = nullptr;
	TargetCameraPoint = nullptr;
	OnHandleFinish.Unbind();
}

float UCameraHandle::GetSwitchDuration_Implementation()
{
	return 0.f;
}
