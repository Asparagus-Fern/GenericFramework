// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CommonButtonEvent.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"

UCommonButtonEvent::UCommonButtonEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Response.Add(ECommonButtonResponseEvent::OnSelected, true);
	Response.Add(ECommonButtonResponseEvent::OnDeselected, false);
}

void UCommonButtonEvent::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();
	Execute_OnActived(this);
}

void UCommonButtonEvent::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();
	Execute_OnInactived(this);
}

void UCommonButtonEvent::NativeOnCreate()
{
	IProcedureBaseInterface::NativeOnCreate();
	Execute_OnCreate(this);
}

void UCommonButtonEvent::NativeOnDestroy()
{
	IProcedureBaseInterface::NativeOnDestroy();
	Execute_OnDestroy(this);
}

void UCommonButtonEvent::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();
	Execute_OnRefresh(this);
}
