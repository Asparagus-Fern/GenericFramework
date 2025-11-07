// Copyright ChenTaiye 2025. All Rights Reserved.

#include "CameraSwitch/GenericCameraSwitchMethod_Transition.h"

#include "CameraPoint/CameraPointBase.h"

UGenericCameraSwitchMethod_Transition::UGenericCameraSwitchMethod_Transition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ViewTargetTransitionParams.BlendTime = 1.f;
	ViewTargetTransitionParams.BlendFunction = VTBlend_Cubic;
	ViewTargetTransitionParams.BlendExp = 0.f;
	ViewTargetTransitionParams.bLockOutgoing = false;
}

bool UGenericCameraSwitchMethod_Transition::HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint)
{
	if (Super::HandleSwitchToCameraPoint_Implementation(InPlayerController, InCameraPoint))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UGenericCameraSwitchMethod_Transition::NativeOnSwitchToCameraPointFinish, ViewTargetTransitionParams.BlendTime);
		OwnerPlayerController->PlayerCameraManager->SetViewTarget(TargetCameraPoint, ViewTargetTransitionParams);
		return true;
	}

	return false;
}

void UGenericCameraSwitchMethod_Transition::OnSwitchToCameraPointFinish_Implementation()
{
	Super::OnSwitchToCameraPointFinish_Implementation();
	TimerHandle.Invalidate();
}

float UGenericCameraSwitchMethod_Transition::GetSwitchDuration_Implementation()
{
	return ViewTargetTransitionParams.BlendTime;
}
