// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/GameplayProcedure.h"

#include "Procedure/ProcedureManager.h"

UWorld* UGameplayProcedure::GetWorld() const
{
	return UProcedureManager::Get()->GetWorld();
}
