// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_SwitchGameMenu.h"

#include "ScreenWidgetManager.h"
#include "DataAsset/GameMenuSetting.h"

bool UCBE_SwitchGameMenu::CanExecuteButtonEvent_Implementation()
{
	return IsValid(GameMenuSetting);
}

void UCBE_SwitchGameMenu::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->SwitchGameMenu(GameMenuSetting);
	}

	if (bIsAsync)
		MarkAsActivedFinish();
}
