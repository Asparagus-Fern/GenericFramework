// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Procedure.h"

#include "Manager/ManagerGlobal.h"
#include "Procedure/ProcedureManager.h"

void UBPFunctions_Procedure::SwitchProcedure(const FGameplayTag InProcedureTag, const bool bForce)
{
	GetManager<UProcedureManager>()->SwitchProcedure(InProcedureTag, bForce);
}

UGameplayProcedure* UBPFunctions_Procedure::GetGameplayProcedure(const FGameplayTag InProcedureTag)
{
	return GetManager<UProcedureManager>()->GetGameplayProcedure(InProcedureTag);
}

FGameplayTag UBPFunctions_Procedure::GetLastProcedureTag()
{
	return GetManager<UProcedureManager>()->GetLastProcedureTag();
}

FGameplayTag UBPFunctions_Procedure::GetCurrentProcedureTag()
{
	return GetManager<UProcedureManager>()->GetCurrentProcedureTag();
}

TMap<FGameplayTag, UGameplayProcedure*>& UBPFunctions_Procedure::GetGameplayProcedureMapping()
{
	return GetManager<UProcedureManager>()->GetGameplayProcedureMapping();
}
