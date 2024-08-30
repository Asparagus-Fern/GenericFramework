// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraHandle.h"

#include "CameraHandleInterface.h"
#include "CameraManager.h"
#include "CameraManagerSetting.h"
#include "CameraPoint/CameraPointBase.h"
#include "Kismet/GameplayStatics.h"

UCameraHandle::FCameraHandleDelegate UCameraHandle::OnSwitchCameraFinish;

UWorld* UCameraHandle::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(), TEXT("CommonButtonEvent: %s has a null OuterPrivate in UCommonButtonEvent::GetWorld()"), *GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		if (const UCameraManager* CameraManager = GetManager<UCameraManager>())
		{
			return CameraManager->GetWorld();
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

		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsWithInterface(this, UCameraHandleInterface::StaticClass(), Actors);
		for (const auto Actor : Actors)
		{
			ICameraHandleInterface::Execute_HandleSwitchToCameraBegin(Actor, this);
		}


		return HandleSwitchToCameraPoint(InPlayerController, InCameraPoint);
	}

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

	if (!TargetCameraPoint->CameraTag.IsValid() && UCameraManagerSetting::Get()->bDestroyEmptyCameraPointAfterSwitchFinish)
	{
		TargetCameraPoint->Destroy();
	}

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(this, UCameraHandleInterface::StaticClass(), Actors);
	for (const auto Actor : Actors)
	{
		ICameraHandleInterface::Execute_HandleSwitchToCameraFinish(Actor, this);
	}

	OwnerPlayerController = nullptr;
	TargetCameraPoint = nullptr;
	OnHandleFinish.Unbind();
}
