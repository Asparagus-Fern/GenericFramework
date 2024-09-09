// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraHandle/CameraHandle_Transition.h"

#include "CameraPoint/CameraPointBase.h"

UCameraHandle_Transition::UCameraHandle_Transition()
{
	ViewTargetTransitionParams.BlendTime = 1.f;
	ViewTargetTransitionParams.BlendFunction = VTBlend_Cubic;
	ViewTargetTransitionParams.BlendExp = 0.f;
	ViewTargetTransitionParams.bLockOutgoing = false;
}

bool UCameraHandle_Transition::HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint)
{
	if (Super::HandleSwitchToCameraPoint_Implementation(InPlayerController, InCameraPoint))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCameraHandle_Transition::NativeOnSwitchToCameraPointFinish, ViewTargetTransitionParams.BlendTime);
		OwnerPlayerController->PlayerCameraManager->SetViewTarget(TargetCameraPoint, ViewTargetTransitionParams);
		return true;
	}

	return false;
}

void UCameraHandle_Transition::OnSwitchToCameraPointFinish_Implementation()
{
	Super::OnSwitchToCameraPointFinish_Implementation();
	TimerHandle.Invalidate();
}

float UCameraHandle_Transition::GetSwitchDuration_Implementation()
{
	return ViewTargetTransitionParams.BlendTime;
}
