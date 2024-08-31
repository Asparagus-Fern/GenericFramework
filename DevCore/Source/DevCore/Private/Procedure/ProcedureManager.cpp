// Fill out your copyright notice in the Description page of Project Settings.


#include "Procedure/ProcedureManager.h"

#include "BPFunctions/BPFunctions_Object.h"
#include "Procedure/ProcedureManagerSetting.h"
#include "Procedure/ProcedureProxy.h"
#include "Procedure/GameplayProcedure/GameplayProcedure.h"

#define LOCTEXT_NAMESPACE "UProcedureManager"

bool UProcedureManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UProcedureManagerSetting::Get()->bEnableSubsystem;
}

void UProcedureManager::NativeOnCreate()
{
	Super::NativeOnCreate();
	FProcedureDelegates::OnProxyHandleBegin.AddUObject(this, &UProcedureManager::OnProcedureProxyHandleBegin);
	FProcedureDelegates::OnProxyHandlePause.AddUObject(this, &UProcedureManager::OnProcedureProxyHandlePause);
	FProcedureDelegates::OnProxyHandleContinue.AddUObject(this, &UProcedureManager::OnProcedureProxyHandleContinue);
	FProcedureDelegates::OnProxyHandleStop.AddUObject(this, &UProcedureManager::OnProcedureProxyHandleStop);
	FProcedureDelegates::OnProxyHandleFinish.AddUObject(this, &UProcedureManager::OnProcedureProxyHandleFinish);

	LoadGameplayProcedure();
}

void UProcedureManager::NativeOnDestroy()
{
	Super::NativeOnDestroy();
	FProcedureDelegates::OnProxyHandleBegin.RemoveAll(this);
	FProcedureDelegates::OnProxyHandlePause.RemoveAll(this);
	FProcedureDelegates::OnProxyHandleContinue.RemoveAll(this);
	FProcedureDelegates::OnProxyHandleStop.RemoveAll(this);
	FProcedureDelegates::OnProxyHandleFinish.RemoveAll(this);
}

void UProcedureManager::OnWorldMatchStarting_Implementation()
{
	Super::OnWorldMatchStarting_Implementation();

	for (auto& SoftGameplayProcedure : UProcedureManagerSetting::Get()->GameplayProcedures)
	{
		if (SoftGameplayProcedure.IsNull())
		{
			continue;
		}

		UGameplayProcedure* GameplayProcedure = UBPFunctions_Object::LoadObject<UGameplayProcedure>(SoftGameplayProcedure);
		if (IsValid(GameplayProcedure) && GameplayProcedure->ProcedureTag.IsValid())
		{
			GameplayProcedures.FindOrAdd(GameplayProcedure->ProcedureTag, GameplayProcedure);
		}
	}

	if (!UProcedureManagerSetting::Get()->DefaultGameplayProcedure.IsNull())
	{
		UGameplayProcedure* GameplayProcedure = UBPFunctions_Object::LoadObject<UGameplayProcedure>(UProcedureManagerSetting::Get()->DefaultGameplayProcedure);
		if (IsValid(GameplayProcedure) && GameplayProcedure->ProcedureTag.IsValid())
		{
			if (!GameplayProcedures.Contains(GameplayProcedure->ProcedureTag))
			{
				GameplayProcedures.FindOrAdd(GameplayProcedure->ProcedureTag, GameplayProcedure);
			}

			SwitchProcedure(GameplayProcedure);
		}
	}
}

void UProcedureManager::SwitchProcedure(UGameplayProcedure* InProcedure, const bool bForce)
{
	if (IsValid(InProcedure) && InProcedure->ProcedureTag.IsValid())
	{
		if (!GameplayProcedures.Contains(InProcedure->ProcedureTag))
		{
			GameplayProcedures.FindOrAdd(InProcedure->ProcedureTag, InProcedure);
		}

		SwitchProcedure(InProcedure->ProcedureTag, bForce);
	}
}

void UProcedureManager::SwitchProcedure(const FGameplayTag InProcedureTag, const bool bForce)
{
	FProcedureHandleGroup ProcedureHandleGroup;

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
				ProcedureHandleGroup.ProcedureHandles.Add(FProcedureHandle(GetGameplayProcedure(CurrentProcedureTag), false));
			}

			/* 进入下一个流程 */
			if (IsValid(GetGameplayProcedure(InProcedureTag)))
			{
				ProcedureHandleGroup.ProcedureHandles.Add(FProcedureHandle(GetGameplayProcedure(InProcedureTag), true));
			}
		}
	}
	else
	{
		/* 进入首个流程 */
		if (IsValid(GetGameplayProcedure(InProcedureTag)))
		{
			ProcedureHandleGroup.ProcedureHandles.Add(FProcedureHandle(GetGameplayProcedure(InProcedureTag), true));
		}
	}

	LastProcedureTag = CurrentProcedureTag;
	CurrentProcedureTag = InProcedureTag;
	FProcedureDelegates::OnGameplayProcedureSwitch.Broadcast(GetGameplayProcedure(LastProcedureTag), GetGameplayProcedure(CurrentProcedureTag));

	RegisterProcedureHandle(ProcedureHandleGroup);
}

FGameplayTag UProcedureManager::GetLastProcedureTag()
{
	return LastProcedureTag;
}

FGameplayTag UProcedureManager::GetCurrentProcedureTag()
{
	return CurrentProcedureTag;
}

UGameplayProcedure* UProcedureManager::GetGameplayProcedure(const FGameplayTag InProcedureTag)
{
	return GameplayProcedures.FindRef(InProcedureTag);
}

TMap<FGameplayTag, UGameplayProcedure*>& UProcedureManager::GetGameplayProcedures()
{
	return GameplayProcedures;
}

UProcedureProxy* UProcedureManager::RegisterProcedureHandle(TArray<UProcedureObject*> InProcedureObjects, const bool InTargetActiveState, const FSimpleDelegate OnFinish)
{
	TArray<FProcedureHandle> ProcedureHandles;

	for (const auto& ProcedureObject : InProcedureObjects)
	{
		ProcedureHandles.Add(FProcedureHandle(ProcedureObject, InTargetActiveState));
	}

	return RegisterProcedureHandle(ProcedureHandles, OnFinish);
}

UProcedureProxy* UProcedureManager::RegisterProcedureHandle(const TArray<FProcedureHandle> InProcedureHandles, const FSimpleDelegate OnFinish)
{
	FProcedureHandleGroup NewProcedureHandleGroup;

	NewProcedureHandleGroup.ProcedureHandles = InProcedureHandles;
	NewProcedureHandleGroup.OnFinish = OnFinish;

	return RegisterProcedureHandle(NewProcedureHandleGroup);
}

UProcedureProxy* UProcedureManager::RegisterProcedureHandle(const FProcedureHandleGroup InHandleGroup)
{
	UProcedureProxy* NewProcedureHandle = NewObject<UProcedureProxy>(this);
	ActivatedProcedureProxy.Add(NewProcedureHandle);

	auto HandleNextTick = [NewProcedureHandle, InHandleGroup]()
	{
		NewProcedureHandle->Handle(InHandleGroup);
	};

	GetWorld()->GetTimerManager().SetTimerForNextTick(HandleNextTick);

	return NewProcedureHandle;
}

void UProcedureManager::OnProcedureProxyHandleBegin(UProcedureProxy* InProcedureProxy)
{
}

void UProcedureManager::OnProcedureProxyHandlePause(UProcedureProxy* InProcedureProxy)
{
}

void UProcedureManager::OnProcedureProxyHandleContinue(UProcedureProxy* InProcedureProxy)
{
}

void UProcedureManager::OnProcedureProxyHandleStop(UProcedureProxy* InProcedureProxy)
{
}

void UProcedureManager::OnProcedureProxyHandleFinish(UProcedureProxy* InProcedureProxy)
{
	if (ActivatedProcedureProxy.Contains(InProcedureProxy))
	{
		ActivatedProcedureProxy.Remove(InProcedureProxy);
		InProcedureProxy->MarkAsGarbage();
	}
}

#undef LOCTEXT_NAMESPACE
