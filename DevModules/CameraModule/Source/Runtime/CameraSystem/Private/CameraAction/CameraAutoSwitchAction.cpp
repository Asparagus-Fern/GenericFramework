// Copyright ChenTaiye 2025. All Rights Reserved.


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
		GenericLOG(GenericLogCamera, Error, TEXT("CameraHandle Is InValid"))
		return;
	}

	if (AutoSwitchTags.IsEmpty())
	{
		GenericLOG(GenericLogCamera, Warning, TEXT("AutoSwitchTags Is Empty"))
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

	if (UCameraManager* CameraManager = GetManagerOwner<UCameraManager>())
	{
		if (CameraManager->CanSwitchToCamera(TagToSwitch))
		{
			CameraManager->SwitchToCamera(GetOwnerPlayerController()->GetLocalPlayer()->GetControllerId(), TagToSwitch, CameraHandle);

			if (!AutoSwitchCameraTimerHandle.IsValid())
			{
				GetWorld()->GetTimerManager().SetTimer(AutoSwitchCameraTimerHandle, this, &UCameraAutoSwitchAction::SwitchToNext, TimeInterval + bIsTimerAfterSwitchFinish ? CameraHandle->GetSwitchDuration() : 0.f, true);
			}
		}
	}
}
