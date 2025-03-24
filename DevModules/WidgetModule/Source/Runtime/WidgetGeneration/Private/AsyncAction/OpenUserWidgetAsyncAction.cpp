// Copyright ChenTaiye 2025. All Rights Reserved.


#include "AsyncAction/OpenUserWidgetAsyncAction.h"

#include "WidgetAnimationManager.h"
#include "WidgetManager.h"
#include "Manager/ManagerStatics.h"

UOpenUserWidgetAsyncAction* UOpenUserWidgetAsyncAction::AsyncOpenUserWidget(UUserWidgetBase* InWidget)
{
	UOpenUserWidgetAsyncAction* NewAction = NewObject<UOpenUserWidgetAsyncAction>();

	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		UWidgetAnimationManager::Delegate_OnWidgetAnimationPlayFinish.AddUObject(NewAction, &UOpenUserWidgetAsyncAction::OnWidgetActivedAnimationFinish);
		WidgetManager->OpenUserWidget(InWidget, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UOpenUserWidgetAsyncAction::OnWidgetActived));
	}

	return NewAction;
}

UOpenUserWidgetAsyncAction* UOpenUserWidgetAsyncAction::AsyncOpenUserWidgetByClass(TSubclassOf<UUserWidgetBase> InWidgetClass)
{
	UOpenUserWidgetAsyncAction* NewAction = NewObject<UOpenUserWidgetAsyncAction>();

	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		UWidgetAnimationManager::Delegate_OnWidgetAnimationPlayFinish.AddUObject(NewAction, &UOpenUserWidgetAsyncAction::OnWidgetActivedAnimationFinish);
		WidgetManager->OpenUserWidget(InWidgetClass, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UOpenUserWidgetAsyncAction::OnWidgetActived));
	}

	return NewAction;
}

void UOpenUserWidgetAsyncAction::OnWidgetActived(UUserWidgetBase* InWidget)
{
	OnFinish.Broadcast(InWidget);
}

void UOpenUserWidgetAsyncAction::OnWidgetActivedAnimationFinish(UUserWidgetBase* InWidget, bool InIsActived)
{
	UWidgetAnimationManager::Delegate_OnWidgetAnimationPlayFinish.RemoveAll(this);
	OnAnimationFinish.Broadcast();
}
