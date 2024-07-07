// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayProcedure/ProcedurePlay.h"

#include "LevelStreamingManager.h"
#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedurePlay_Default, "Procedure.Play.Default");

void UProcedurePlay::NativeOnActived()
{
	Super::NativeOnActived();

	GetManager<UScreenWidgetManager>()->OpenUserWidget(DefaultOpenWidgets);
	GetManager<UScreenWidgetManager>()->SwitchGameMenu(GameMenuSetting);

	RequestActivateFinish();
}

void UProcedurePlay::NativeOnInactived()
{
	Super::NativeOnInactived();
	RequestInactivateFinish();
}
