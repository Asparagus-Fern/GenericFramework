// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CommonButtonEvent.h"

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
