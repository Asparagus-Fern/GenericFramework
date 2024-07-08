// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/ProcedureManager.h"

#include "Manager/ManagerGlobal.h"
#include "Procedure/GameplayProcedure.h"
#include "Procedure/ProcedureHandle.h"
#include "StaticFunctions/StaticFunctions_Object.h"

#define LOCTEXT_NAMESPACE "UProcedureManager"

UProcedureManager::UProcedureManager()
{
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
}

void UProcedureManager::NativeOnInactived()
{
	Super::NativeOnInactived();

	LastProcedureTag = FGameplayTag::EmptyTag;
	CurrentProcedureTag = FGameplayTag::EmptyTag;

	// for (const auto& ActiveProcedureHandle : ActiveProcedureHandles)
	// {
	// 	ActiveProcedureHandle->Reset();
	// 	ActiveProcedureHandle->MarkAsGarbage();
	// }

	for (const auto& Procedure : GameplayProcedure)
	{
		if (Procedure.Value->GetIsActive())
		{
			Procedure.Value->NativeOnInactived();
		}
	}

	ActiveProcedureHandles.Reset();
	GameplayProcedure.Reset();
}

FText UProcedureManager::GetManagerDisplayName()
{
	return LOCTEXT("DisplayName", "Procedure Manager");
}

void UProcedureManager::NativeOnBeginPlay()
{
	Super::NativeOnBeginPlay();

	if (DefaultProcedureTag.IsValid())
	{
		SwitchProcedure(DefaultProcedureTag);
	}
}

void UProcedureManager::NativeOnEndPlay()
{
	Super::NativeOnEndPlay();
}

void UProcedureManager::SwitchProcedure(FGameplayTag InProcedureTag, bool bForce)
{
	TArray<FProcedureInterfaceHandle> ProcedureInterfaceHandles;

	if (CurrentProcedureTag.IsValid())
	{
		if (CurrentProcedureTag == InProcedureTag)
		{
			/* 已经是指定流程但强制刷新 */
			if (bForce)
			{
				UGameplayProcedure* CurrentGameplayProcedure = GetGameplayProcedure(InProcedureTag);
				CurrentGameplayProcedure->NativeOnRefresh();
				return;
			}
		}
		else
		{
			/* 退出上一个流程 */
			if (IsValid(GetGameplayProcedure(CurrentProcedureTag)))
			{
				ProcedureInterfaceHandles.Add(FProcedureInterfaceHandle(GetGameplayProcedure(CurrentProcedureTag), false));
			}

			/* 进入下一个流程 */
			if (IsValid(GetGameplayProcedure(InProcedureTag)))
			{
				ProcedureInterfaceHandles.Add(FProcedureInterfaceHandle(GetGameplayProcedure(InProcedureTag), true));
			}
		}
	}
	else
	{
		/* 进入首个流程 */
		if (IsValid(GetGameplayProcedure(InProcedureTag)))
		{
			ProcedureInterfaceHandles.Add(FProcedureInterfaceHandle(GetGameplayProcedure(InProcedureTag), true));
		}
	}

	LastProcedureTag = CurrentProcedureTag;
	CurrentProcedureTag = InProcedureTag;
	RegisterProcedureHandle(ProcedureInterfaceHandles);
}

UGameplayProcedure* UProcedureManager::GetGameplayProcedure(FGameplayTag InProcedureTag)
{
	/* 返回缓存 */
	if (GameplayProcedure.Contains(InProcedureTag))
	{
		return GameplayProcedure.FindRef(InProcedureTag);
	}
	else
	{
		/* 软引用加载 */
		if (GameplayProcedureObjects.Contains(InProcedureTag))
		{
			const TSoftObjectPtr<UGameplayProcedure> FoundGameplayProcedureClass = GameplayProcedureObjects.FindRef(InProcedureTag);
			if (!FoundGameplayProcedureClass.IsNull())
			{
				UGameplayProcedure* LoadGameplayProcedure = FStaticFunctions_Object::LoadObject<UGameplayProcedure>(FoundGameplayProcedureClass);
				if (IsValid(LoadGameplayProcedure))
				{
					GameplayProcedure.Add(InProcedureTag, LoadGameplayProcedure);
					LoadGameplayProcedure->NativeOnCreate();
					return LoadGameplayProcedure;
				}
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

UProcedureHandle* UProcedureManager::RegisterProcedureHandle(const TArray<FProcedureInterfaceHandle>& InHandles, FSimpleMulticastDelegate OnHandleFinish, FSimpleMulticastDelegate OnHandleReset)
{
	UProcedureHandle* NewProcedureHandle = NewObject<UProcedureHandle>(this);
	ActiveProcedureHandles.Add(NewProcedureHandle);

	FSimpleMulticastDelegate OnFinish;
	OnFinish.AddLambda([this, NewProcedureHandle, OnHandleFinish]()
		{
			ActiveProcedureHandles.Remove(NewProcedureHandle);
			OnHandleFinish.Broadcast();
			NewProcedureHandle->MarkAsGarbage();
		}
	);

	FSimpleMulticastDelegate OnReset;
	OnReset.AddLambda([this, NewProcedureHandle, OnHandleReset]()
		{
			OnHandleReset.Broadcast();
			ActiveProcedureHandles.Remove(NewProcedureHandle);
			NewProcedureHandle->MarkAsGarbage();
		}
	);

	NewProcedureHandle->Handle(InHandles, OnFinish, OnReset);
	return NewProcedureHandle;
}

void UProcedureManager::ResetProcedureHandle(UProcedureHandle* InHandle)
{
	InHandle->Reset();
}

#undef LOCTEXT_NAMESPACE
