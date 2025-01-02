// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveNode/ActiveNode_Play.h"

#include "CameraManager.h"
#include "ScreenWidgetManager.h"
#include "CameraHandle/CameraHandle.h"
#include "DataAsset/GameMenuSetting.h"
#include "Manager/ManagerProxy.h"

AActiveNode_Play::AActiveNode_Play()
{
}

void AActiveNode_Play::LoginNode_Implementation()
{
	Super::LoginNode_Implementation();

	if (const UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		if (ScreenWidgetManager->IsGameHUDCreated())
		{
			PostHUDCreated();
		}
		else
		{
			UScreenWidgetManager::PostHUDCreated.AddUObject(this, &AActiveNode_Play::PostHUDCreated);
		}
	}

	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		if (DefaultCameraTag.IsValid() && IsValid(CameraHandle))
		{
			if (CameraManager->CanCameraSwitch(DefaultCameraTag))
			{
				CameraManager->SwitchToCamera(0, DefaultCameraTag, CameraHandle);
			}
			else
			{
				UCameraManager::Delegate_OnCameraPointRegister.AddUObject(this, &AActiveNode_Play::OnCameraPointRegister);
			}
		}
	}
}

void AActiveNode_Play::LogoutNode_Implementation()
{
	Super::LogoutNode_Implementation();

	UScreenWidgetManager::PostHUDCreated.RemoveAll(this);
	UCameraManager::Delegate_OnCameraPointRegister.RemoveAll(this);

	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		for (const auto& DefaultOpenWidget : DefaultOpenWidgets)
		{
			ScreenWidgetManager->CloseUserWidget(DefaultOpenWidget);
		}
	}
}

void AActiveNode_Play::PostHUDCreated()
{
	UScreenWidgetManager::PostHUDCreated.RemoveAll(this);

	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		for (const auto& DefaultOpenWidgetClass : DefaultOpenWidgetClasses)
		{
			if (UUserWidgetBase* Widget = ScreenWidgetManager->OpenUserWidget(DefaultOpenWidgetClass))
			{
				DefaultOpenWidgets.Add(Widget);
			}
		}

		if (IsValid(DefaultGameMenu))
		{
			ScreenWidgetManager->SwitchGameMenu(DefaultGameMenu);
		}
	}
}

void AActiveNode_Play::OnCameraPointRegister(ACameraPointBase* InCameraPoint)
{
	UCameraManager::Delegate_OnCameraPointRegister.RemoveAll(this);

	if (UCameraManager* CameraManager = UManagerProxy::Get()->GetManager<UCameraManager>())
	{
		if (InCameraPoint->CameraTag == DefaultCameraTag)
		{
			CameraManager->SwitchToCamera(0, DefaultCameraTag, CameraHandle);
		}
	}
}
