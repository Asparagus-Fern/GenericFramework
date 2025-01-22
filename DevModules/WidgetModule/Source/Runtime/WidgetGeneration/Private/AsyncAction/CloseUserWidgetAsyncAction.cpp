// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/CloseUserWidgetAsyncAction.h"

#include "WidgetAnimationManager.h"
#include "WidgetManager.h"
#include "Manager/ManagerStatics.h"

UCloseUserWidgetAsyncAction* UCloseUserWidgetAsyncAction::AsyncCloseUserWidget(UUserWidgetBase* InWidget, const bool MarkAsGarbage)
{
	UCloseUserWidgetAsyncAction* NewAction = NewObject<UCloseUserWidgetAsyncAction>();

	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		UWidgetAnimationManager::Delegate_OnWidgetAnimationPlayFinish.AddUObject(NewAction, &UCloseUserWidgetAsyncAction::OnWidgetInactivedAnimationFinish);
		WidgetManager->CloseUserWidget(InWidget, MarkAsGarbage, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UCloseUserWidgetAsyncAction::OnWidgetInactived));
	}

	return NewAction;
}

UCloseUserWidgetAsyncAction* UCloseUserWidgetAsyncAction::AsyncCloseUserWidgetByTag(const FGameplayTag InSlotTag, const bool MarkAsGarbage)
{
	UCloseUserWidgetAsyncAction* NewAction = NewObject<UCloseUserWidgetAsyncAction>();

	if (UWidgetManager* WidgetManager = GetManager<UWidgetManager>())
	{
		UWidgetAnimationManager::Delegate_OnWidgetAnimationPlayFinish.AddUObject(NewAction, &UCloseUserWidgetAsyncAction::OnWidgetInactivedAnimationFinish);
		WidgetManager->CloseUserWidget(InSlotTag, MarkAsGarbage, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UCloseUserWidgetAsyncAction::OnWidgetInactived));
	}

	return NewAction;
}

void UCloseUserWidgetAsyncAction::OnWidgetInactived(UUserWidgetBase* InWidget)
{
	OnFinish.Broadcast();
}

void UCloseUserWidgetAsyncAction::OnWidgetInactivedAnimationFinish(UUserWidgetBase* InWidget, bool InIsActived)
{
	UWidgetAnimationManager::Delegate_OnWidgetAnimationPlayFinish.RemoveAll(this);
	OnAnimationFinish.Broadcast();
}
