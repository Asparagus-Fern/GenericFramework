// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/Menu/MenuStyle.h"

#include "Event/CommonButtonEvent.h"
#include "UserWidget/Base/UserWidgetBase.h"

void UMenuStyle::PreConstructMenuStyle_Implementation(FMenuInfo InMenuInfo)
{
}

void UMenuStyle::NativePreConstructMenuStyle(FMenuInfo InMenuInfo)
{
	MenuInfo = InMenuInfo;
	ActivedEvents = MenuInfo.ActivedEvents;
	InactivedEvents = MenuInfo.InactivedEvents;
	ResponseState = MenuInfo.ResponseState;

	PreConstructMenuStyle(InMenuInfo);
}

void UMenuStyle::ConstructMenuStyle_Implementation(FMenuInfo InMenuInfo)
{
}

void UMenuStyle::NativeConstructMenuStyle(FMenuInfo InMenuInfo)
{
	ConstructMenuStyle(InMenuInfo);

	if (IsValid(ActiveCommonButton))
	{
		if (!MenuInfo.bHidden)
		{
			ActiveCommonButton->SetIsEnabled(MenuInfo.bIsEnable);
			ActiveCommonButton->SetIsSelectable(MenuInfo.bSelectable);
			ActiveCommonButton->SetIsToggleable(MenuInfo.bToggleable);
		}
	}
	else
	{
		LOG(Debug_UI, Error, TEXT("CommonButton Is NULL"))
	}

	SetVisibility(MenuInfo.bHidden ? ESlateVisibility::Collapsed : ESlateVisibility::SelfHitTestInvisible);
}
