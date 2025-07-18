// Copyright ChenTaiye 2025. All Rights Reserved.


#include "GameHUDSettings.h"

#include "GameplayTagsSettings.h"
#include "Base/GenericGameHUD.h"
#include "StaticFunctions/StaticFunctions_Object.h"

UGameHUDSettings::UGameHUDSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	if (const TSubclassOf<UGenericGameHUD> MainHUD = LoadClass<UGenericGameHUD>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/WidgetModule/UMG/HUD/WBP_GameHUD_Main.WBP_GameHUD_Main_C'")))
	{
		GenericHUDClasses.AddUnique(MainHUD.Get());
	}

	if (const TSubclassOf<UGenericGameHUD> GameHUD = LoadClass<UGenericGameHUD>(nullptr,TEXT("/Script/UMGEditor.WidgetBlueprint'/WidgetModule/UMG/HUD/WBP_GameHUD_Game.WBP_GameHUD_Game_C'")))
	{
		GenericHUDClasses.AddUnique(GameHUD.Get());
	}
#endif
}
