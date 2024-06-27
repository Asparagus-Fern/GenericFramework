// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/GameplayProcedure.h"

#include "Procedure/ProcedureManager.h"

void UGameplayProcedure::NativeOnCreate()
{
	IProcedureInterface::NativeOnCreate();
	Execute_OnCreate(this);
}

void UGameplayProcedure::NativeOnDestroy()
{
	IProcedureInterface::NativeOnDestroy();
	Execute_OnDestroy(this);
}

void UGameplayProcedure::NativeOnRefresh()
{
	IProcedureInterface::NativeOnRefresh();
	Execute_OnRefresh(this);
}

void UGameplayProcedure::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();
	Execute_OnActived(this);
}

void UGameplayProcedure::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();
	Execute_OnInactived(this);
}
