// Fill out your copyright notice in the Description page of Project Settings.

#include "Procedure/ProcedureInterface.h"

#include "Debug/DebugType.h"

void IProcedureInterface::NativeOnActived()
{
	IProcedureInterface::Execute_OnActived(Cast<UObject>(this));
	SetIsActived(true);
	DLOG(DLogManager, Log, TEXT("On Actived : %s"), *Cast<UObject>(this)->GetName());
}

void IProcedureInterface::NativeOnInactived()
{
	IProcedureInterface::Execute_OnInactived(Cast<UObject>(this));
	SetIsActived(false);
	DLOG(DLogManager, Log, TEXT("On Inactived : %s"), *Cast<UObject>(this)->GetName());
}
