// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/ProcedureObject.h"

void UProcedureObject::NativeOnCreate()
{
	IProcedureInterface::NativeOnCreate();
	IProcedureInterface::Execute_OnCreate(this);
}

void UProcedureObject::NativeOnDestroy()
{
	IProcedureInterface::NativeOnDestroy();
	IProcedureInterface::Execute_OnDestroy(this);
}

void UProcedureObject::NativeOnRefresh()
{
	IProcedureInterface::NativeOnRefresh();
	IProcedureInterface::Execute_OnRefresh(this);
}

void UProcedureObject::NativeOnActived()
{
	bIsActived = true;
	IProcedureInterface::NativeOnActived();
	IProcedureInterface::Execute_OnActived(this);
}

void UProcedureObject::NativeOnInactived()
{
	bIsActived = false;
	IProcedureInterface::NativeOnInactived();
	IProcedureInterface::Execute_OnInactived(this);
}

void UProcedureObject::MarkAsActivedFinish_Implementation()
{
	NativeOnActivedFinish.ExecuteIfBound();
}

void UProcedureObject::MarkAsInactivedFinish_Implementation()
{
	NativeOnInactivedFinish.ExecuteIfBound();
}
