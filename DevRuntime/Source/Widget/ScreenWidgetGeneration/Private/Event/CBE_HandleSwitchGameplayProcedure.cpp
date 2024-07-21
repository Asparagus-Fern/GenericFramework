// Fill out your copyright notice in the Description page of Project Settings.


#include "Event/CBE_HandleSwitchGameplayProcedure.h"

#include "Manager/ManagerGlobal.h"
#include "Procedure/ProcedureManager.h"

void UCBE_HandleSwitchGameplayProcedure::NativeOnActived()
{
	Super::NativeOnActived();

	FSimpleMulticastDelegate OnFinish;
	OnFinish.AddUObject(this, &UCBE_HandleSwitchGameplayProcedure::OnActiveGameplayProcedureSwitchFinish);
	GetManager<UProcedureManager>()->SwitchProcedure(SwitchGameplayProcedureTagOnActive, false, OnFinish);
}

void UCBE_HandleSwitchGameplayProcedure::NativeOnInactived()
{
	Super::NativeOnInactived();

	FSimpleMulticastDelegate OnFinish;
	OnFinish.AddUObject(this, &UCBE_HandleSwitchGameplayProcedure::OnInactiveGameplayProcedureSwitchFinish);
	GetManager<UProcedureManager>()->SwitchProcedure(SwitchGameplayProcedureTagOnInactive, false, OnFinish);
}

void UCBE_HandleSwitchGameplayProcedure::OnActiveGameplayProcedureSwitchFinish()
{
	RequestActivateFinish();
}

void UCBE_HandleSwitchGameplayProcedure::OnInactiveGameplayProcedureSwitchFinish()
{
	RequestInactivateFinish();
}
