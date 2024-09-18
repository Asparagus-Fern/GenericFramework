// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveNode/ActiveNode_Play.h"

#include "ScreenWidgetManager.h"
#include "DataAsset/GameMenuSetting.h"

AActiveNode_Play::AActiveNode_Play()
{
}

void AActiveNode_Play::Login()
{
	Super::Login();

	if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->PostHUDCreated.AddDynamic(this, &AActiveNode_Play::PostHUDCreated);
	}
}

void AActiveNode_Play::Logout()
{
	Super::Logout();

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
