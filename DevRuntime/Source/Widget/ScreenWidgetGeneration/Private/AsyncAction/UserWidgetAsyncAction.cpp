// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/UserWidgetAsyncAction.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"

UUserWidgetAsyncAction* UUserWidgetAsyncAction::AsyncOpenUserWidget(UUserWidgetBase* InWidget)
{
	UUserWidgetAsyncAction* NewAction = NewObject<UUserWidgetAsyncAction>();

	FSimpleMulticastDelegate OnHandleFinish;
	OnHandleFinish.AddUObject(NewAction, &UUserWidgetAsyncAction::OnHandleFinish);
	GetManager<UScreenWidgetManager>()->OpenUserWidget(InWidget, OnHandleFinish);

	return NewAction;
}

UUserWidgetAsyncAction* UUserWidgetAsyncAction::AsyncOpenUserWidgetByClass(TSubclassOf<UUserWidgetBase> InWidgetClass, UUserWidgetBase*& NewWidget)
{
	UUserWidgetAsyncAction* NewAction = NewObject<UUserWidgetAsyncAction>();
	NewWidget = GetManager<UScreenWidgetManager>()->CreateUserWidget(InWidgetClass);

	FSimpleMulticastDelegate OnHandleFinish;
	OnHandleFinish.AddUObject(NewAction, &UUserWidgetAsyncAction::OnHandleFinish);
	GetManager<UScreenWidgetManager>()->OpenUserWidget(InWidgetClass, OnHandleFinish);

	return NewAction;
}

UUserWidgetAsyncAction* UUserWidgetAsyncAction::AsyncCloseUserWidget(UUserWidgetBase* InWidget)
{
	UUserWidgetAsyncAction* NewAction = NewObject<UUserWidgetAsyncAction>();

	FSimpleMulticastDelegate OnHandleFinish;
	OnHandleFinish.AddUObject(NewAction, &UUserWidgetAsyncAction::OnHandleFinish);
	GetManager<UScreenWidgetManager>()->CloseUserWidget(InWidget, OnHandleFinish);

	return NewAction;
}

UUserWidgetAsyncAction* UUserWidgetAsyncAction::AsyncCloseUserWidgetByTag(FGameplayTag InSlotTag)
{
	UUserWidgetAsyncAction* NewAction = NewObject<UUserWidgetAsyncAction>();

	FSimpleMulticastDelegate OnHandleFinish;
	OnHandleFinish.AddUObject(NewAction, &UUserWidgetAsyncAction::OnHandleFinish);
	GetManager<UScreenWidgetManager>()->CloseUserWidget(InSlotTag, OnHandleFinish);

	return NewAction;
}

void UUserWidgetAsyncAction::OnHandleFinish()
{
	OnFinish.Broadcast();
}
