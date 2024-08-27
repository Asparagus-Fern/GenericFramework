// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonButtonEvent/CBE_HandleMenuSelection.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"

bool UCBE_HandleMenuSelection::CanExecuteButtonEvent_Implementation()
{
	return TargetMenuTag.IsValid();
}

void UCBE_HandleMenuSelection::ExecuteButtonEvent_Implementation()
{
	Super::ExecuteButtonEvent_Implementation();

	if (TargetState)
		GetManager<UScreenWidgetManager>()->SelectMenu(TargetMenuTag);
	else
		GetManager<UScreenWidgetManager>()->DeselectMenu(TargetMenuTag);

	/* todo:处理异步 */
	if (bIsAsync)
	{
		MarkAsActivedFinish();
	}
}
