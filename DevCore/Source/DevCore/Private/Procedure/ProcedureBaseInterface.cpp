// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/ProcedureBaseInterface.h"

#include "Debug/DebugType.h"

void IProcedureBaseInterface::NativeOnCreate()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IProcedureBaseInterface::Execute_OnCreate(Object);
		DLOG(DLogManager, Log, TEXT("On Created : %s"), *Object->GetName());
	}
}

void IProcedureBaseInterface::NativeOnDestroy()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IProcedureBaseInterface::Execute_OnDestroy(Object);
		DLOG(DLogManager, Log, TEXT("On Destroy : %s"), *Object->GetName());
	}
}

void IProcedureBaseInterface::NativeOnRefresh()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IProcedureBaseInterface::Execute_OnRefresh(Object);
	}
}
