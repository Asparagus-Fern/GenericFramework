// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Procedure.h"

#include "Manager/ManagerGlobal.h"
#include "Procedure/ProcedureManager.h"

void UBPFunctions_Procedure::SwitchProcedure(const UObject* WorldContextObject, const FGameplayTag InProcedureTag, const bool bForce)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UProcedureManager* ProcedureManager = GetManager<UProcedureManager>(World))
		{
			ProcedureManager->SwitchProcedure(InProcedureTag, bForce);
		}
	}
}

UGameplayProcedure* UBPFunctions_Procedure::GetGameplayProcedure(const UObject* WorldContextObject, const FGameplayTag InProcedureTag)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UProcedureManager* ProcedureManager = GetManager<UProcedureManager>(World))
		{
			return ProcedureManager->GetGameplayProcedure(InProcedureTag);
		}
	}

	return nullptr;
}

FGameplayTag UBPFunctions_Procedure::GetLastProcedureTag(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UProcedureManager* ProcedureManager = GetManager<UProcedureManager>(World))
		{
			return ProcedureManager->GetLastProcedureTag();
		}
	}

	return FGameplayTag::EmptyTag;
}

FGameplayTag UBPFunctions_Procedure::GetCurrentProcedureTag(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UProcedureManager* ProcedureManager = GetManager<UProcedureManager>(World))
		{
			return ProcedureManager->GetCurrentProcedureTag();
		}
	}

	return FGameplayTag::EmptyTag;
}

bool UBPFunctions_Procedure::GetGameplayProcedures(const UObject* WorldContextObject, TMap<FGameplayTag, UGameplayProcedure*>& GameplayProcedures)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		if (UProcedureManager* ProcedureManager = GetManager<UProcedureManager>(World))
		{
			GameplayProcedures = ProcedureManager->GetGameplayProcedures();
			return true;
		}
	}

	return false;
}
