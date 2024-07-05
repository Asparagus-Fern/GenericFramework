// Fill out your copyright notice in the Description page of Project Settings.

#include "Procedure/ProcedureInterface.h"

void IProcedureInterface::NativeOnActived()
{
	SetIsActive(true);
}

void IProcedureInterface::NativeOnInactived()
{
	SetIsActive(false);
}

void IProcedureInterface::SetIsActive(const bool InActive)
{
	bIsActive = InActive;
}

void IProcedureInterface::RequestActivateFinish() const
{
	OnActivedFinish.Broadcast();
}

void IProcedureInterface::RequestInactivateFinish() const
{
	OnInactivedFinish.Broadcast();
}
