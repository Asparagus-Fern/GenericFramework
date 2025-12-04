// Copyright ChenTaiye 2025. All Rights Reserved.

#include "WidgetSettings.h"

#include "GameplayTagsSettings.h"
#include "Base/GenericGameHUD.h"
#include "StaticFunctions/StaticFunctions_Object.h"

UWidgetSettings::UWidgetSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	if (const TSubclassOf<UGenericGameHUD> MainHUD = LoadClass<UGenericGameHUD>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/GenericWidget/UMG/HUD/WBP_GameHUD_Main.WBP_GameHUD_Main_C'")))
	{
		GenericHUDClasses.AddUnique(MainHUD.Get());
	}

	if (const TSubclassOf<UGenericGameHUD> GameHUD = LoadClass<UGenericGameHUD>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/GenericWidget/UMG/HUD/WBP_GameHUD_Game.WBP_GameHUD_Game_C'")))
	{
		GenericHUDClasses.AddUnique(GameHUD.Get());
	}
#endif
}
