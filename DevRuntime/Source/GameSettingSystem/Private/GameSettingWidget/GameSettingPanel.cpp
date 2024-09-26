// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSettingWidget/GameSettingPanel.h"

#include "ScreenWidgetManager.h"

bool UGameSettingPanel::Initialize()
{
	return Super::Initialize();
}

void UGameSettingPanel::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UGameSettingPanel::NativeConstruct()
{
	Super::NativeConstruct();

	if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	{
		PreviewGameMenuSetting = ScreenWidgetManager->GameMenu;
		if (GameMenuSetting)
		{
			ScreenWidgetManager->SwitchGameMenu(GameMenuSetting);
		}
	}
}
