// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CommonButtonEvent.h"

UCommonButtonEvent::UCommonButtonEvent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ResponseEvent.Add(ECommonButtonResponseEvent::OnSelected, true);
	ResponseEvent.Add(ECommonButtonResponseEvent::OnDeselected, false);
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
