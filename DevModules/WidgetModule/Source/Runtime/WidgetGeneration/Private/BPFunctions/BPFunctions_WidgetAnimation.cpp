// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_WidgetAnimation.h"

#include "WidgetAnimationManager.h"
#include "Manager/ManagerStatics.h"

bool UBPFunctions_WidgetAnimation::PlayWidgetAnimation(UUserWidgetBase* InWidget, bool InIsActive)
{
	if (UWidgetAnimationManager* WidgetAnimationManager = GetManager<UWidgetAnimationManager>())
	{
		WidgetAnimationManager->PlayWidgetAnimation(InWidget, InIsActive);
	}
	return false;
}
