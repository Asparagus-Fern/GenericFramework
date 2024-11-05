// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/ProcedureBaseInterface.h"

#include "Debug/DebugType.h"

void IProcedureBaseInterface::NativeOnCreate()
{
	IProcedureBaseInterface::Execute_OnCreate(Cast<UObject>(this));
	DLOG(DLogManager, Log, TEXT("On Created : %s"), *Cast<UObject>(this)->GetName());
}

void IProcedureBaseInterface::NativeOnDestroy()
{
	IProcedureBaseInterface::Execute_OnDestroy(Cast<UObject>(this));
	DLOG(DLogManager, Log, TEXT("On Destroy : %s"), *Cast<UObject>(this)->GetName());
}

void IProcedureBaseInterface::NativeOnRefresh()
{
	IProcedureBaseInterface::Execute_OnRefresh(Cast<UObject>(this));
}
