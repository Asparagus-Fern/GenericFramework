// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/CloseUserWidgetAsyncAction.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerProxy.h"

UCloseUserWidgetAsyncAction* UCloseUserWidgetAsyncAction::AsyncCloseUserWidget(UUserWidgetBase* InWidget, bool MarkAsGarbage)
{
	UCloseUserWidgetAsyncAction* NewAction = NewObject<UCloseUserWidgetAsyncAction>();

	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->CloseUserWidget(InWidget, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UCloseUserWidgetAsyncAction::OnHandleFinish), MarkAsGarbage);
	}

	return NewAction;
}

UCloseUserWidgetAsyncAction* UCloseUserWidgetAsyncAction::AsyncCloseUserWidgetByTag(FGameplayTag InSlotTag, bool MarkAsGarbage)
{
	UCloseUserWidgetAsyncAction* NewAction = NewObject<UCloseUserWidgetAsyncAction>();

	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->CloseUserWidget(InSlotTag, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UCloseUserWidgetAsyncAction::OnHandleFinish), MarkAsGarbage);
	}

	return NewAction;
}

void UCloseUserWidgetAsyncAction::OnHandleFinish(UUserWidgetBase* InWidget)
{
	OnFinish.Broadcast();
}
