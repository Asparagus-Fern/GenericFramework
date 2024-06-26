// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Procedure.h"

#include "Procedure/ProcedureManager.h"

bool UBPFunctions_Procedure::SwitchProcedure(EGameplayProcedure InProcedure)
{
	return GetManager<UProcedureManager>()->SwitchProcedure(InProcedure);
}
