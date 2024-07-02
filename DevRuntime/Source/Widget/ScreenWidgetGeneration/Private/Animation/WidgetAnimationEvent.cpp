// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/WidgetAnimationEvent.h"

void UWidgetAnimationEvent::NativeOnOpen(UUserWidgetBase* InUserWidget)
{
	IWidgetAnimationInterface::NativeOnOpen(InUserWidget);
	Execute_OnOpen(this, InUserWidget);
}

void UWidgetAnimationEvent::NativeOnClose(UUserWidgetBase* InUserWidget)
{
	IWidgetAnimationInterface::NativeOnClose(InUserWidget);
	Execute_OnClose(this, InUserWidget);
}

void UWidgetAnimationEvent::RequestAnimationFinish()
{
	GetOnAnimationFinishDelegate().Broadcast();
}
