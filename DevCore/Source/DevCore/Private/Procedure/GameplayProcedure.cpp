// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/GameplayProcedure.h"

#include "Manager/ManagerGlobal.h"
#include "Procedure/ProcedureManager.h"

UGameplayProcedure::UGameplayProcedure()
{
}

void UGameplayProcedure::NativeOnCreate()
{
	IProcedureBaseInterface::NativeOnCreate();
	Execute_OnCreate(this);
}

void UGameplayProcedure::NativeOnDestroy()
{
	IProcedureBaseInterface::NativeOnDestroy();
	Execute_OnDestroy(this);
}

void UGameplayProcedure::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();
	Execute_OnRefresh(this);
}

void UGameplayProcedure::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();
	PreProcedureActived.Broadcast();
	Execute_OnActived(this);
}

void UGameplayProcedure::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();
	PreProcedureInactived.Broadcast();
	Execute_OnInactived(this);
}

void UGameplayProcedure::RequestProcedureActived_Implementation()
{
	RequestActivateFinish();
	PostProcedureActived.Broadcast();

	if (bIsAutoActivateNextProcedure)
	{
		GetManager<UProcedureManager>()->SwitchProcedure(NextProcedureTag);
	}
}

void UGameplayProcedure::RequestProcedureInactived_Implementation()
{
	RequestInactivateFinish();
	PostProcedureInactived.Broadcast();
}
