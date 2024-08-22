// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraHandle/CameraHandle_Default.h"

#include "CameraPoint/CameraPointBase.h"

UCameraHandle_Default::UCameraHandle_Default()
{
	ViewTargetTransitionParams.BlendTime = 1.f;
	ViewTargetTransitionParams.BlendFunction = VTBlend_Linear;
	ViewTargetTransitionParams.BlendExp = 0.f;
	ViewTargetTransitionParams.bLockOutgoing = false;
}

bool UCameraHandle_Default::HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint)
{
	if (Super::HandleSwitchToCameraPoint_Implementation(InPlayerController, InCameraPoint))
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UCameraHandle_Default::NativeOnSwitchToCameraPointFinish, ViewTargetTransitionParams.BlendTime);
		OwnerPlayerController->PlayerCameraManager->SetViewTarget(TargetCameraPoint, ViewTargetTransitionParams);
		return true;
	}

	return false;
}

void UCameraHandle_Default::OnSwitchToCameraPointFinish_Implementation()
{
	Super::OnSwitchToCameraPointFinish_Implementation();
	OwnerPlayerController->PlayerCameraManager->SetViewTarget(OwnerPlayerController->GetPawn());
	TimerHandle.Invalidate();
}
