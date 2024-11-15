// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncAction/MoveUserWidgetAsyncAction.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerProxy.h"

UMoveUserWidgetAsyncAction* UMoveUserWidgetAsyncAction::AsyncMoveUserWidget(const FGameplayTag OriginSlotTag, const FGameplayTag TargetSlotTag)
{
	UMoveUserWidgetAsyncAction* NewAction = NewObject<UMoveUserWidgetAsyncAction>();

	if (UScreenWidgetManager* ScreenWidgetManager = UManagerProxy::Get()->GetManager<UScreenWidgetManager>())
	{
		ScreenWidgetManager->MoveUserWidget(OriginSlotTag, TargetSlotTag, FOnWidgetActiveStateChanged::CreateUObject(NewAction, &UMoveUserWidgetAsyncAction::OnHandleFinish));
	}

	return NewAction;
}

void UMoveUserWidgetAsyncAction::OnHandleFinish(UUserWidgetBase* InWidget)
{
	OnFinish.Broadcast(InWidget);
}
