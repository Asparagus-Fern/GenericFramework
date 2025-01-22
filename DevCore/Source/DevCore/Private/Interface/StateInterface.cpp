// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/StateInterface.h"

#include "Debug/DebugType.h"

void IStateInterface::NativeOnCreate()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IStateInterface::Execute_OnCreate(Object);
		DLOG(DLogProcedure, Log, TEXT("On Created : %s"), *Object->GetName());
	}
}

void IStateInterface::NativeOnActived()
{
	SetIsActived(true);

	if (UObject* Object = Cast<UObject>(this))
	{
		IStateInterface::Execute_OnActived(Object);
		DLOG(DLogProcedure, Log, TEXT("On Actived : %s"), *Object->GetName());
	}
}

void IStateInterface::NativeOnActivedFinish()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		OnActivedFinishDelegate.Broadcast(Object);
		IStateInterface::Execute_OnActivedFinish(Object);
		DLOG(DLogProcedure, Log, TEXT("On Actived Finish : %s"), *Object->GetName());
	}
}

void IStateInterface::NativeOnRefresh()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IStateInterface::Execute_OnRefresh(Object);
	}
}

void IStateInterface::NativeOnInactived()
{
	SetIsActived(false);

	if (UObject* Object = Cast<UObject>(this))
	{
		OnInactivedFinishDelegate.Broadcast(Object);
		IStateInterface::Execute_OnInactived(Object);
		DLOG(DLogProcedure, Log, TEXT("On Inactived : %s"), *Object->GetName());
	}
}

void IStateInterface::NativeOnInactivedFinish()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IStateInterface::Execute_OnInactivedFinish(Object);
		DLOG(DLogProcedure, Log, TEXT("On Inactived Finish : %s"), *Object->GetName());
	}
}

void IStateInterface::NativeOnDestroy()
{
	if (UObject* Object = Cast<UObject>(this))
	{
		IStateInterface::Execute_OnDestroy(Object);
		DLOG(DLogProcedure, Log, TEXT("On Destroy : %s"), *Object->GetName());

		if (bGarbageAtDestroy)
		{
			Object->MarkAsGarbage();
		}
	}
}
