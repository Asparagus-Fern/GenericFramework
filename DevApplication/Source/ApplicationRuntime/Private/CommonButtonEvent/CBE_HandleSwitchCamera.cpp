// Fill out your copyright notice in the Description page of Project Settings.

#include "CommonButtonEvent/CBE_HandleSwitchCamera.h"

#include "CameraManager.h"
#include "SceneManager.h"
#include "Camera/CameraActor.h"
#include "CameraHandle/CameraHandle_Transition.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/ManagerProxy.h"

UCBE_HandleSwitchCamera::UCBE_HandleSwitchCamera()
{
	bIsAsync = true;
	TargetCameraHandle = CreateDefaultSubobject<UCameraHandle_Transition>("CameraHandle");
}

bool UCBE_HandleSwitchCamera::CanExecuteButtonEvent_Implementation()
{
	bool IsValidPlayer = false;
	if (const UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		IsValidPlayer = IsValid(UGameplayStatics::GetPlayerController(CameraManager, TargetPlayerIndex));
	}

	const bool IsValidTag = bUseUnrealCamera ? (TargetCameraNameTag != NAME_None) : TargetCameraGameplayTag.IsValid();
	const bool IsValidHandle = IsValid(TargetCameraHandle);

	return IsValidPlayer && IsValidTag && IsValidHandle;
}

void UCBE_HandleSwitchCamera::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	TDelegate<void()> OnSwitchFinish;
	if (bIsAsync)
	{
		OnSwitchFinish = FSimpleDelegate::CreateLambda([this]()
			{
				MarkAsActivedFinish();
			}
		);
	}

	UCameraHandle* CameraHandle = nullptr;
	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		if (bUseUnrealCamera)
		{
			if (const USceneManager* SceneManager = UManagerProxy::Get()->GetManager<USceneManager>())
			{
				TArray<AActor*> Actors = SceneManager->FindActors(FFindActorHandle(TargetCameraNameTag));
				if (!Actors.IsEmpty())
				{
					if (ACameraActor* CameraActor = Cast<ACameraActor>(Actors[0]))
					{
						CameraHandle = CameraManager->SwitchToCamera(TargetPlayerIndex, CameraActor, TargetCameraHandle, OnSwitchFinish);
					}
				}
			}
		}
		else
		{
			CameraHandle = CameraManager->SwitchToCamera(TargetPlayerIndex, TargetCameraGameplayTag, TargetCameraHandle, OnSwitchFinish);
		}
	}

	if (!bIsAsync || !IsValid(CameraHandle))
	{
		MarkAsActivedFinish();
	}
}
