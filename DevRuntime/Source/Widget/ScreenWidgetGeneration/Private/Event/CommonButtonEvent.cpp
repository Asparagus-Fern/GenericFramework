// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CommonButtonEvent.h"

#include "ScreenWidgetManager.h"
#include "Manager/ManagerGlobal.h"

UCommonButtonEvent::UCommonButtonEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ResponseEvent.Add(ECommonButtonResponseEvent::OnSelected, true);
	ResponseEvent.Add(ECommonButtonResponseEvent::OnDeselected, false);
}

UWorld* UCommonButtonEvent::GetWorld() const
{
	return GetManager<UScreenWidgetManager>()->GetWorld();
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
