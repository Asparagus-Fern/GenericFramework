// Copyright ChenTaiye 2025. All Rights Reserved.

#include "CameraSwitch/GenericCameraSwitchMethod.h"

#include "CameraPoint/CameraPointBase.h"

bool UGenericCameraSwitchMethod::HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint)
{
	return true;
}

bool UGenericCameraSwitchMethod::NativeHandleSwitchToCameraPoint(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint, FSimpleDelegate OnFinish)
{
	if (IsValid(InPlayerController) && IsValid(InCameraPoint))
	{
		OwnerPlayerController = InPlayerController;
		TargetCameraPoint = InCameraPoint;
		OnHandleFinish = OnFinish;

		OnSwitchCameraBegin.Broadcast(this);
		return HandleSwitchToCameraPoint(InPlayerController, InCameraPoint);
	}

	OnFinish.ExecuteIfBound();
	return false;
}

void UGenericCameraSwitchMethod::OnSwitchToCameraPointReset_Implementation()
{
	NativeOnSwitchToCameraPointFinish();
}

void UGenericCameraSwitchMethod::NativeOnSwitchToCameraPointReset()
{
	OnSwitchToCameraPointReset();
}

void UGenericCameraSwitchMethod::OnSwitchToCameraPointFinish_Implementation()
{
}

void UGenericCameraSwitchMethod::NativeOnSwitchToCameraPointFinish()
{
	OnSwitchToCameraPointFinish();

	OnHandleFinish.ExecuteIfBound();
	OnSwitchCameraFinish.Broadcast(this);

	if (IsValid(TargetCameraPoint) && !TargetCameraPoint->CameraTag.IsValid())
	{
		TargetCameraPoint->Destroy();
	}

	OwnerPlayerController = nullptr;
	TargetCameraPoint = nullptr;
	OnHandleFinish.Unbind();
}

float UGenericCameraSwitchMethod::GetSwitchDuration_Implementation()
{
	return 0.f;
}
