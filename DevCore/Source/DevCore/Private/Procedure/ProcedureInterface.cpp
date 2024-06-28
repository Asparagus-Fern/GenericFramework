// Fill out your copyright notice in the Description page of Project Settings.

#include "Procedure/ProcedureInterface.h"

void IProcedureInterface::NativeOnActived()
{
	bIsActive = true;
}

void IProcedureInterface::NativeOnInactived()
{
	bIsActive = false;
}

void IProcedureInterface::RequestActivedFinish() const
{
	OnActivedFinish.Broadcast();
}

void IProcedureInterface::RequestInactivedFinish() const
{
	OnInactivedFinish.Broadcast();
}
