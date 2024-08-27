// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/CloseUserWidgetAsyncAction.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"

UCloseUserWidgetAsyncAction* UCloseUserWidgetAsyncAction::AsyncCloseUserWidget(UUserWidgetBase* InWidget)
{
	UCloseUserWidgetAsyncAction* NewAction = NewObject<UCloseUserWidgetAsyncAction>();
	
	if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->CloseUserWidget(InWidget, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UCloseUserWidgetAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

UCloseUserWidgetAsyncAction* UCloseUserWidgetAsyncAction::AsyncCloseUserWidgetByTag(FGameplayTag InSlotTag)
{
	UCloseUserWidgetAsyncAction* NewAction = NewObject<UCloseUserWidgetAsyncAction>();

	if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->CloseUserWidget(InSlotTag, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UCloseUserWidgetAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

void UCloseUserWidgetAsyncAction::OnHandleFinish(UUserWidgetBase* InWidget)
{
	OnFinish.Broadcast();
}
