// Copyright ChenTaiye 2025. All Rights Reserved.

#include "CameraSwitch/CameraSwitchMethod.h"

#include "CameraManager.h"
#include "CameraPoint/CameraPointBase.h"
#include "CameraSwitch/CameraSwitchInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ManagerStatics.h"

UWorld* UCameraSwitchMethod::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(), TEXT("CommonButtonEvent: %s has a null OuterPrivate in UCommonButtonEvent::GetWorld()"), *GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		if (const UCameraManager* CameraManager = GetManagerOwner<UCameraManager>())
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

void UCameraSwitchMethod::Reset()
{
	NativeOnSwitchToCameraPointReset();
}

bool UCameraSwitchMethod::HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint)
{
	return true;
}

bool UCameraSwitchMethod::NativeHandleSwitchToCameraPoint(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint, FSimpleDelegate OnFinish)
{
	if (IsValid(InPlayerController) && IsValid(InCameraPoint))
	{
		OwnerPlayerController = InPlayerController;
		TargetCameraPoint = InCameraPoint;
		OnHandleFinish = OnFinish;

		OnSwitchCameraBegin.Broadcast(this);

		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsWithInterface(this, UCameraSwitchInterface::StaticClass(), Actors);
		for (const auto Actor : Actors)
		{
			ICameraSwitchInterface::Execute_HandleSwitchToCameraBegin(Actor, this);
		}

		return HandleSwitchToCameraPoint(InPlayerController, InCameraPoint);
	}

	OnFinish.ExecuteIfBound();
	return false;
}

void UCameraSwitchMethod::OnSwitchToCameraPointReset_Implementation()
{
	NativeOnSwitchToCameraPointFinish();
}

void UCameraSwitchMethod::NativeOnSwitchToCameraPointReset()
{
	OnSwitchToCameraPointReset();
}

void UCameraSwitchMethod::OnSwitchToCameraPointFinish_Implementation()
{
}

void UCameraSwitchMethod::NativeOnSwitchToCameraPointFinish()
{
	OnSwitchToCameraPointFinish();

	OnHandleFinish.ExecuteIfBound();
	OnSwitchCameraFinish.Broadcast(this);

	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsWithInterface(this, UCameraSwitchInterface::StaticClass(), Actors);
	for (const auto Actor : Actors)
	{
		ICameraSwitchInterface::Execute_HandleSwitchToCameraFinish(Actor, this);
	}

	if (IsValid(TargetCameraPoint) && !TargetCameraPoint->CameraTag.IsValid())
	{
		TargetCameraPoint->Destroy();
	}

	OwnerPlayerController = nullptr;
	TargetCameraPoint = nullptr;
	OnHandleFinish.Unbind();
}

float UCameraSwitchMethod::GetSwitchDuration_Implementation()
{
	return 0.f;
}
