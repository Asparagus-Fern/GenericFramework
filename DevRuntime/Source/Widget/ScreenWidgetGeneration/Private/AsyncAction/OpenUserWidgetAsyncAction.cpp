// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/OpenUserWidgetAsyncAction.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"

UOpenUserWidgetAsyncAction* UOpenUserWidgetAsyncAction::AsyncOpenUserWidget(UUserWidgetBase* InWidget)
{
	UOpenUserWidgetAsyncAction* NewAction = NewObject<UOpenUserWidgetAsyncAction>();

	if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->OpenUserWidget(InWidget, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UOpenUserWidgetAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

UOpenUserWidgetAsyncAction* UOpenUserWidgetAsyncAction::AsyncOpenUserWidgetByClass(TSubclassOf<UUserWidgetBase> InWidgetClass)
{
	UOpenUserWidgetAsyncAction* NewAction = NewObject<UOpenUserWidgetAsyncAction>();

	if (UScreenWidgetManager* ScreenWidgetManager = GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->OpenUserWidget(InWidgetClass, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UOpenUserWidgetAsyncAction::OnHandleFinish));
	}
	
	return NewAction;
}

void UOpenUserWidgetAsyncAction::OnHandleFinish(UUserWidgetBase* InWidget)
{
	OnFinish.Broadcast(InWidget);
}
