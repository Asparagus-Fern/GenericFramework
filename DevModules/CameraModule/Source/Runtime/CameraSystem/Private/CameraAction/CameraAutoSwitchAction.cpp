// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraAction/CameraAutoSwitchAction.h"

#include "CameraManager.h"
#include "CameraSwitch/CameraSwitchMethod.h"
#include "Manager/ManagerStatics.h"

UCameraAutoSwitchAction::UCameraAutoSwitchAction(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bEnableReverse = false;
}

void UCameraAutoSwitchAction::HandleStartAction()
{
	Super::HandleStartAction();

	if (!IsValid(CameraHandle))
	{
		DLOG(DLogCamera, Error, TEXT("CameraHandle Is InValid"))
		return;
	}

	if (AutoSwitchTags.IsEmpty())
	{
		DLOG(DLogCamera, Warning, TEXT("AutoSwitchTags Is Empty"))
		return;
	}

	SwitchToNext();
}

void UCameraAutoSwitchAction::HandleStopAction()
{
	Super::HandleStopAction();

	AutoSwitchCameraTimerHandle.Invalidate();
}

void UCameraAutoSwitchAction::SwitchToNext()
{
	CurrentIndex++;
	const FGameplayTag TagToSwitch = AutoSwitchTags.IsValidIndex(CurrentIndex) ? AutoSwitchTags[CurrentIndex] : AutoSwitchTags[0];

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		if (CameraManager->CanSwitchToCamera(TagToSwitch))
		{
			CameraManager->SwitchToCamera(GetOwnerPlayerController()->GetLocalPlayer()->GetControllerId(), TagToSwitch, CameraHandle);

			if (!AutoSwitchCameraTimerHandle.IsValid())
			{
				GetWorld()->GetTimerManager().SetTimer(AutoSwitchCameraTimerHandle, this, &UCameraAutoSwitchAction::SwitchToNext, TimeInterval + bIsTimerAfrerSwitchFinsih ? CameraHandle->GetSwitchDuration() : 0.f, true);
			}
		}
	}
}
