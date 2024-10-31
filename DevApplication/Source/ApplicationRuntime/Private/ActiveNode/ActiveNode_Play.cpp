// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveNode/ActiveNode_Play.h"

#include "CameraManager.h"
#include "ScreenWidgetManager.h"
#include "CameraHandle/CameraHandle.h"
#include "DataAsset/GameMenuSetting.h"

AActiveNode_Play::AActiveNode_Play()
{
}

void AActiveNode_Play::Login()
{
	Super::Login();

	if (const UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
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

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		if (DefaultCameraTag.IsValid() && IsValid(CameraHandle))
		{
			if (CameraManager->CanCameraSwitch(DefaultCameraTag))
			{
				CameraManager->SwitchToCamera(0, DefaultCameraTag, CameraHandle);
			}
			else
			{
				UCameraManager::OnCameraPointRegister.AddUObject(this, &AActiveNode_Play::OnCameraPointRegister);
			}
		}
	}
}

void AActiveNode_Play::Logout()
{
	Super::Logout();

	UScreenWidgetManager::PostHUDCreated.RemoveAll(this);
	UCameraManager::OnCameraPointRegister.RemoveAll(this);

	if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	{
		for (const auto& DefaultOpenWidget : DefaultOpenWidgets)
		{
			ScreenWidgetManager->CloseUserWidget(DefaultOpenWidget);
		}
	}
}

void AActiveNode_Play::PostHUDCreated()
{
	if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->PostHUDCreated.RemoveAll(this);

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
	UCameraManager::OnCameraPointRegister.RemoveAll(this);

	if (UCameraManager* CameraManager = GetManager<UCameraManager>())
	{
		if (InCameraPoint->CameraTag == DefaultCameraTag)
		{
			CameraManager->SwitchToCamera(0, DefaultCameraTag, CameraHandle);
		}
	}
}
