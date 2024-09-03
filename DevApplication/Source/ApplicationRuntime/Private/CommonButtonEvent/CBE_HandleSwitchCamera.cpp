// Fill out your copyright notice in the Description page of Project Settings.

#include "CommonButtonEvent/CBE_HandleSwitchCamera.h"

#include "CameraManager.h"
#include "CameraHandle/CameraHandle_Transition.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ManagerGlobal.h"

UCBE_HandleSwitchCamera::UCBE_HandleSwitchCamera()
{
	bIsAsync = true;
	TargetCameraHandle = CreateDefaultSubobject<UCameraHandle_Transition>("CameraHandle");
}

bool UCBE_HandleSwitchCamera::CanExecuteButtonEvent_Implementation()
{
	bool IsValidPlayer = false;
	if (const UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		IsValidPlayer = IsValid(UGameplayStatics::GetPlayerCharacter(CameraManager, TargetPlayerIndex));
	}

	return IsValidPlayer && TargetCameraTag.IsValid() && IsValid(TargetCameraHandle);
}

void UCBE_HandleSwitchCamera::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	const auto OnSwitchFinish = FSimpleDelegate::CreateLambda([this]()
		{
			MarkAsActivedFinish();
		}
	);

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		if (bIsAsync)
			CameraManager->SwitchToCamera(TargetPlayerIndex, TargetCameraTag, TargetCameraHandle, OnSwitchFinish);
		else
			CameraManager->SwitchToCamera(TargetPlayerIndex, TargetCameraTag, TargetCameraHandle);
	}
	else
	{
		if (bIsAsync)
			MarkAsActivedFinish();
	}
}
