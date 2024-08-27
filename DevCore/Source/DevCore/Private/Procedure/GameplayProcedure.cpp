// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/GameplayProcedure.h"

#include "Manager/ManagerGlobal.h"
#include "Procedure/ProcedureManager.h"

void UGameplayProcedure::MarkAsActivedFinish_Implementation()
{
	Super::MarkAsActivedFinish_Implementation();

	if (bIsAutoActivateNextProcedure)
	{
		GetManager<UProcedureManager>()->SwitchProcedure(NextProcedureTag);
	}
}

void UGameplayProcedure::MarkAsInactivedFinish_Implementation()
{
	Super::MarkAsInactivedFinish_Implementation();
}
