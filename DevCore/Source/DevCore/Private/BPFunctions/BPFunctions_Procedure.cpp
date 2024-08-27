// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Procedure.h"

#include "Manager/ManagerGlobal.h"
#include "Procedure/ProcedureManager.h"

void UBPFunctions_Procedure::SwitchProcedure(const FGameplayTag InProcedureTag, const bool bForce)
{
	if (UProcedureManager* ProcedureManager = GetManager<UProcedureManager>())
	{
		ProcedureManager->SwitchProcedure(InProcedureTag, bForce);
	}
}

UGameplayProcedure* UBPFunctions_Procedure::GetGameplayProcedure(const FGameplayTag InProcedureTag)
{
	if (UProcedureManager* ProcedureManager = GetManager<UProcedureManager>())
	{
		return ProcedureManager->GetGameplayProcedure(InProcedureTag);
	}

	return nullptr;
}

FGameplayTag UBPFunctions_Procedure::GetLastProcedureTag()
{
	if (UProcedureManager* ProcedureManager = GetManager<UProcedureManager>())
	{
		return ProcedureManager->GetLastProcedureTag();
	}

	return FGameplayTag::EmptyTag;
}

FGameplayTag UBPFunctions_Procedure::GetCurrentProcedureTag()
{
	if (UProcedureManager* ProcedureManager = GetManager<UProcedureManager>())
	{
		return ProcedureManager->GetCurrentProcedureTag();
	}

	return FGameplayTag::EmptyTag;
}

bool UBPFunctions_Procedure::GetGameplayProcedures(TMap<FGameplayTag, UGameplayProcedure*>& GameplayProcedures)
{
	if (UProcedureManager* ProcedureManager = GetManager<UProcedureManager>())
	{
		GameplayProcedures = ProcedureManager->GetGameplayProcedures();
		return true;
	}

	return false;
}
