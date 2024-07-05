// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/WidgetAnimationEvent.h"

#include "ScreenWidgetType.h"

void UWidgetAnimationEvent::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();
	IProcedureInterface::Execute_OnActived(this);
}

void UWidgetAnimationEvent::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();
	IProcedureInterface::Execute_OnInactived(this);
}

void UWidgetAnimationEvent::RequestAnimationFinish()
{
	if (GetIsActive())
	{
		RequestActivateFinish();
	}
	else
	{
		RequestInactivateFinish();
	}

	FScreenWidgetDelegates::OnWidgetAnimationFinish.Broadcast(TargetWidget);
}

UWidget* UWidgetAnimationEvent::GetTargetWidget() const
{
	return TargetWidget;
}

void UWidgetAnimationEvent::SetTargetWidget(UWidget* InWidget)
{
	TargetWidget = InWidget;
}
