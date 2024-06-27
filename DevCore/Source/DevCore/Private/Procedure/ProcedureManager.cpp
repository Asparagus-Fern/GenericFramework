// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/ProcedureManager.h"

#include "Manager/ManagerGlobal.h"
#include "Manager/ManagerSubsystem.h"
#include "Procedure/GameplayProcedure.h"
#include "StaticFunctions/StaticFunctions_Object.h"

#define LOCTEXT_NAMESPACE "UProcedureManager"

UProcedureManager::UProcedureManager()
{
}

FText UProcedureManager::GetManagerDisplayName()
{
	return LOCTEXT("DisplayName", "Procedure Manager");
}

void UProcedureManager::NativeOnCreate()
{
	Super::NativeOnCreate();
}

void UProcedureManager::NativeOnDestroy()
{
	Super::NativeOnDestroy();
	GameplayProcedure.Reset();
}

void UProcedureManager::NativeOnActived()
{
	Super::NativeOnActived();

	/* 游戏的开始 */
	if (DefaultProcedureTag.IsValid())
	{
		SwitchProcedure(DefaultProcedureTag);
	}
}

void UProcedureManager::NativeOnInactived()
{
	Super::NativeOnInactived();
}

void UProcedureManager::SwitchProcedure(FGameplayTag InProcedureTag, bool bForce)
{
	if (CurrentProcedureTag == InProcedureTag)
	{
		if (bForce)
		{
			UGameplayProcedure* CurrentGameplayProcedure = GetGameplayProcedure(InProcedureTag);
			CurrentGameplayProcedure->NativeOnRefresh();
		}
	}
	else
	{
		UGameplayProcedure* EndGameplayProcedure = GetGameplayProcedure(InProcedureTag);
		if (IsValid(EndGameplayProcedure))
		{
			EndGameplayProcedure->NativeOnInactived();
		}

		LastProcedureTag = CurrentProcedureTag;
		CurrentProcedureTag = InProcedureTag;

		UGameplayProcedure* BeginGameplayProcedure = GetGameplayProcedure(InProcedureTag);
		if (IsValid(BeginGameplayProcedure))
		{
			BeginGameplayProcedure->NativeOnActived();
		}
	}
}

UGameplayProcedure* UProcedureManager::GetGameplayProcedure(FGameplayTag InProcedureTag)
{
	if (GameplayProcedure.Contains(InProcedureTag))
	{
		return GameplayProcedure.FindRef(InProcedureTag);
	}
	else
	{
		if (GameplayProcedureObjects.Contains(InProcedureTag))
		{
			const TSoftObjectPtr<UGameplayProcedure> FoundGameplayProcedureClass = GameplayProcedureObjects.FindRef(InProcedureTag);
			if (!FoundGameplayProcedureClass.IsNull())
			{
				UGameplayProcedure* LoadGameplayProcedure = FStaticFunctions_Object::LoadObject<UGameplayProcedure>(FoundGameplayProcedureClass);
				GameplayProcedure.Add(InProcedureTag, LoadGameplayProcedure);
				LoadGameplayProcedure->NativeOnCreate();
			}
			else
			{
				DEBUG(Debug_Procedure, Warning, TEXT("GameplayProcedureClass is NULL"))
			}
		}
		else
		{
			DEBUG(Debug_Procedure, Warning, TEXT("GameplayProcedureClass is Not Contain ProcedureTag : %s"), *InProcedureTag.ToString())
		}
	}

	return nullptr;
}

#undef LOCTEXT_NAMESPACE
