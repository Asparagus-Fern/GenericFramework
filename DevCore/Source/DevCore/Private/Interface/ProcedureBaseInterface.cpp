// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Interface/ProcedureBaseInterface.h"

#include "Debug/DebugType.h"

void IProcedureBaseInterface::NativeOnCreate()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IProcedureBaseInterface::Execute_OnCreate(Object);
		DLOG(DLogProcedure, Log, TEXT("On Created : %s"), *Object->GetName());
	}
}

void IProcedureBaseInterface::NativeOnRefresh()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IProcedureBaseInterface::Execute_OnRefresh(Object);
	}
}

void IProcedureBaseInterface::NativeOnDestroy()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IProcedureBaseInterface::Execute_OnDestroy(Object);
		DLOG(DLogProcedure, Log, TEXT("On Destroy : %s"), *Object->GetName());
	}
}
