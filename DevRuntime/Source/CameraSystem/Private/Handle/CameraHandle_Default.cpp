// Fill out your copyright notice in the Description page of Project Settings.


#include "Handle/CameraHandle_Default.h"

#include "CameraPoint/CameraPointBase.h"

UCameraHandle_Default::UCameraHandle_Default()
{
	ViewTargetTransitionParams.BlendTime = 1.f;
	ViewTargetTransitionParams.BlendFunction = VTBlend_Linear;
	ViewTargetTransitionParams.BlendExp = 0.f;
	ViewTargetTransitionParams.bLockOutgoing = false;
}

void UCameraHandle_Default::HandleSwitchToCameraPoint_Implementation(APlayerController* InPlayerController, ACameraPointBase* InCameraPoint)
{
	if (!InPlayerController)
	{
		DEBUG(Debug_Viewport, Error, TEXT("PlayerController Is NULL"))
		return;
	}

	if (!InCameraPoint)
	{
		DEBUG(Debug_Viewport, Error, TEXT("CameraPoint Is NULL"))
		return;
	}

	Super::HandleSwitchToCameraPoint_Implementation(InPlayerController, InCameraPoint);

	/* Create Camera Point For Blend View Target */
	if (!IsValid(PreviewCameraPoint))
	{
		PreviewCameraPoint = GetWorld()->SpawnActor<ACameraPointBase>();
		PreviewCameraPoint->SetActorLabel("CameraPoint_Preview");
	}

	PreviewCameraPoint->SetActorLocation(InPlayerController->PlayerCameraManager->GetCameraLocation());
	PreviewCameraPoint->SetActorRotation(InPlayerController->PlayerCameraManager->GetCameraRotation());
	InPlayerController->PlayerCameraManager->SetViewTarget(PreviewCameraPoint);
	InPlayerController->PlayerCameraManager->SetViewTarget(InCameraPoint, ViewTargetTransitionParams);
}

void UCameraHandle_Default::OnSwitchToCameraPointFinish_Implementation()
{
	Super::OnSwitchToCameraPointFinish_Implementation();

	if (!bLockCamera)
	{
		OwnerPlayerController->PlayerCameraManager->SetViewTarget(OwnerPlayerController->GetPawn());
	}
}
