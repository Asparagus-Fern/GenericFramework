// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CBE_HandleMenuSelection.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"

void UCBE_HandleMenuSelection::NativeOnActived()
{
	Super::NativeOnActived();
	GetManager<UScreenWidgetManager>()->DeselectMenu(ActiveDeselectMenuTag);
	GetManager<UScreenWidgetManager>()->SelectMenu(ActiveSelectMenuTag);
}

void UCBE_HandleMenuSelection::NativeOnInactived()
{
	Super::NativeOnInactived();
	GetManager<UScreenWidgetManager>()->DeselectMenu(InactiveDeselectMenuTag);
	GetManager<UScreenWidgetManager>()->SelectMenu(InactiveSelectMenuTag);
}
