// Fill out your copyright notice in the Description page of Project Settings.


#include "UserWidget/Menu/MenuStyle.h"

#include "Debug/DebugType.h"
#include "UserWidget/Base/UserWidgetBase.h"

UMenuStyle::UMenuStyle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bToggleable = true;
}

void UMenuStyle::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UMenuStyle::NativeOnClicked()
{
	Super::NativeOnClicked();
	FScreenWidgetDelegates::OnMenuClicked.Broadcast(MenuInfo);
}

void UMenuStyle::NativeOnSelected(bool bBroadcast)
{
	Super::NativeOnSelected(bBroadcast);
	FScreenWidgetDelegates::OnMenuSelectionChanged.Broadcast(MenuInfo, true);
}

void UMenuStyle::NativeOnDeselected(bool bBroadcast)
{
	Super::NativeOnDeselected(bBroadcast);
	FScreenWidgetDelegates::OnMenuSelectionChanged.Broadcast(MenuInfo, false);
}

void UMenuStyle::NativeConstructMenuStyle(FMenuInfo InMenuInfo)
{
	MenuInfo = InMenuInfo;
	ConstructMenuStyle(InMenuInfo);
}
