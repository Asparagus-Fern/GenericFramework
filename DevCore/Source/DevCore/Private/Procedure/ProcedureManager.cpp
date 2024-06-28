// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/ProcedureManager.h"

#include "Manager/ManagerGlobal.h"
#include "Manager/ManagerSubsystem.h"
#include "Procedure/GameplayProcedure.h"
#include "Procedure/ProcedureHandle.h"
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

	LastProcedureTag = FGameplayTag::EmptyTag;
	CurrentProcedureTag = FGameplayTag::EmptyTag;

	for (const auto& Procedure : GameplayProcedure)
	{
		Procedure.Value->NativeOnInactived();
	}
	GameplayProcedure.Reset();
}

void UProcedureManager::SwitchProcedure(FGameplayTag InProcedureTag, bool bForce)
{
	UProcedureHandle* ProcedureHandle = NewObject<UProcedureHandle>(this);
	TArray<FProcedureInterfaceHandle> ProcedureInterfaceHandles;

	if (CurrentProcedureTag.IsValid())
	{
		if (CurrentProcedureTag == InProcedureTag)
		{
			if (bForce)
			{
				UGameplayProcedure* CurrentGameplayProcedure = GetGameplayProcedure(InProcedureTag);
				CurrentGameplayProcedure->NativeOnRefresh();
				return;
			}
		}
		else
		{
			if (IsValid(GetGameplayProcedure(CurrentProcedureTag)))
			{
				ProcedureInterfaceHandles.Add(FProcedureInterfaceHandle(GetGameplayProcedure(CurrentProcedureTag), false));
			}

			if (IsValid(GetGameplayProcedure(InProcedureTag)))
			{
				ProcedureInterfaceHandles.Add(FProcedureInterfaceHandle(GetGameplayProcedure(InProcedureTag), true));
			}
		}
	}
	else
	{
		if (IsValid(GetGameplayProcedure(InProcedureTag)))
		{
			ProcedureInterfaceHandles.Add(FProcedureInterfaceHandle(GetGameplayProcedure(InProcedureTag), true));
		}
	}

	LastProcedureTag = CurrentProcedureTag;
	CurrentProcedureTag = InProcedureTag;
	ProcedureHandle->Handle(ProcedureInterfaceHandles);
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
				return LoadGameplayProcedure;
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
