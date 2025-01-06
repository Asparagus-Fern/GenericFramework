// Fill out your copyright notice in the Description page of Project Settings.

#include "Interface/ProcedureInterface.h"

#include "Debug/DebugType.h"

void IProcedureInterface::NativeOnActived()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IProcedureInterface::Execute_OnActived(Object);
		SetIsActived(true);
		DLOG(DLogProcedure, Log, TEXT("On Actived : %s"), *Object->GetName());
	}
}

void IProcedureInterface::NativeOnInactived()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IProcedureInterface::Execute_OnInactived(Object);
		SetIsActived(false);
		DLOG(DLogProcedure, Log, TEXT("On Inactived : %s"), *Object->GetName());
	}
}
