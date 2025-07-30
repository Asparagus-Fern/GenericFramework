// Copyright ChenTaiye 2025. All Rights Reserved.


#include "ProcedureFlow/Play/ProcedureFlow_PlaySmartCity.h"

#include "CameraManager.h"
#include "CameraSwitch/CameraSwitchMethod.h"
#include "Manager/ManagerStatics.h"

AProcedureFlow_PlaySmartCity::AProcedureFlow_PlaySmartCity()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProcedureFlow_PlaySmartCity::OnProcedureFlowEnter_Implementation()
{
	Super::OnProcedureFlowEnter_Implementation();

	// if (const UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	// {
	// if (ScreenWidgetManager->IsGameHUDCreated())
	// {
	// 	PostHUDCreated();
	// }
	// else
	// {
	// 	UScreenWidgetManager::PostHUDCreated.AddUObject(this, &AProcedureFlow_PlaySmartCity::PostHUDCreated);
	// }
	// }

	if (UCameraManager* CameraManager = GetManagerOwner<UCameraManager>())
	{
		if (DefaultCameraTag.IsValid() && IsValid(CameraHandle))
		{
			if (CameraManager->CanSwitchToCamera(DefaultCameraTag))
			{
				CameraManager->SwitchToCamera(0, DefaultCameraTag, CameraHandle);
			}
			else
			{
				UCameraManager::Delegate_OnCameraPointRegister.AddUObject(this, &AProcedureFlow_PlaySmartCity::OnCameraPointRegister);
			}
		}
	}
}

void AProcedureFlow_PlaySmartCity::OnProcedureFlowExit_Implementation()
{
	Super::OnProcedureFlowExit_Implementation();

	// UScreenWidgetManager::PostHUDCreated.RemoveAll(this);
	UCameraManager::Delegate_OnCameraPointRegister.RemoveAll(this);

	// if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	// {
	// 	for (const auto& DefaultOpenWidget : DefaultOpenWidgets)
	// 	{
	// 		ScreenWidgetManager->CloseUserWidget(DefaultOpenWidget);
	// 	}
	// }
}

void AProcedureFlow_PlaySmartCity::PostHUDCreated()
{
	// UScreenWidgetManager::PostHUDCreated.RemoveAll(this);

	// if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	// {
	// 	for (const auto& DefaultOpenWidgetClass : DefaultOpenWidgetClasses)
	// 	{
	// if (UUserWidgetBase* Widget = ScreenWidgetManager->OpenUserWidget(DefaultOpenWidgetClass))
	// {
	// 	DefaultOpenWidgets.Add(Widget);
	// }
	// 	}
	//
	// 	if (IsValid(DefaultGameMenu))
	// 	{
	// 		ScreenWidgetManager->SwitchGameMenu(DefaultGameMenu);
	// 	}
	// }
}

void AProcedureFlow_PlaySmartCity::OnCameraPointRegister(ACameraPointBase* InCameraPoint)
{
	UCameraManager::Delegate_OnCameraPointRegister.RemoveAll(this);

	if (UCameraManager* CameraManager = GetManagerOwner<UCameraManager>())
	{
		if (InCameraPoint->CameraTag == DefaultCameraTag)
		{
			CameraManager->SwitchToCamera(0, DefaultCameraTag, CameraHandle);
		}
	}
}
