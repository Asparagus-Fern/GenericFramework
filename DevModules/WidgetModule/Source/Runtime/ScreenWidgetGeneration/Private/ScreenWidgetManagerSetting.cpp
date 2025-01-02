// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenWidgetManagerSetting.h"

#include "GameplayTagsSettings.h"
#include "UserWidget/HUD/GameHUD.h"

UScreenWidgetManagerSetting::UScreenWidgetManagerSetting(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (const TSubclassOf<UGameHUD> MainHUD = LoadClass<UGameHUD>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/DevApplication/_Develop/UI/HUD/WBP_HUD_Main.WBP_HUD_Main_C'")))
	{
		GameHUDClasses.Add(MainHUD.Get());
	}

	if (const TSubclassOf<UGameHUD> SmartCityHUD = LoadClass<UGameHUD>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/DevApplication/_Develop/UI/HUD/SmartCity/WBP_HUD_SmartCity.WBP_HUD_SmartCity_C'")))
	{
		GameHUDClasses.Add(SmartCityHUD.Get());
	}

	if (UGameplayTagsSettings* GameplayTagsSettings = GetMutableDefault<UGameplayTagsSettings>())
	{
		if (const UDataTable* MainHUDTagTable = LoadObject<UDataTable>(nullptr,TEXT("/Script/Engine.DataTable'/DevApplication/_Develop/DataTable/DT_HUD_Main.DT_HUD_Main'")))
		{
			if (!GameplayTagsSettings->GameplayTagTableList.Contains(MainHUDTagTable->GetPathName()))
			{
				GameplayTagsSettings->GameplayTagTableList.Add(FSoftObjectPath(MainHUDTagTable));
			}
		}

		if (const UDataTable* SmartCityHUDTagTable = LoadObject<UDataTable>(nullptr,TEXT("/Script/Engine.DataTable'/DevApplication/_Develop/DataTable/DT_HUD_SmartCity.DT_HUD_SmartCity'")))
		{
			if (!GameplayTagsSettings->GameplayTagTableList.Contains(SmartCityHUDTagTable->GetPathName()))
			{
				GameplayTagsSettings->GameplayTagTableList.Add(FSoftObjectPath(SmartCityHUDTagTable));
			}
		}
	}
}
