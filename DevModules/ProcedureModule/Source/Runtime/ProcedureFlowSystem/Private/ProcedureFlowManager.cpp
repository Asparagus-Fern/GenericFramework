// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcedureFlowManager.h"

#include "ProcedureFlowComponent.h"
#include "ProcedureFlowSetting.h"

bool UProcedureFlowManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UProcedureFlowManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UProcedureFlowManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool UProcedureFlowManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UProcedureFlowManager::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldMatchStarting(InWorld);
}

void UProcedureFlowManager::HandleOnWorldBeginPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldBeginPlay(InWorld);

	SortProcedureFlowComponentsAsInitialize();
	Execute([](UProcedureFlowComponent* Component)
		{
			IProcedureFlowInterface::Execute_OnProcedureFlowInitialized(Component);
		}
	);

	if (const UProcedureFlowComponent* FirstProcedureFlow = GetProcedureFlowComponent(UProcedureFlowSetting::Get()->DefaultFlowTag))
	{
		EnterProcedureFlow(FirstProcedureFlow->FlowTag);
	}
}

void UProcedureFlowManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldEndPlay(InWorld);

	SortProcedureFlowComponentsAsDeinitialize();
	Execute([](UProcedureFlowComponent* Component)
		{
			IProcedureFlowInterface::Execute_OnProcedureFlowDeinitialize(Component);
		}
	);
}

void UProcedureFlowManager::RegisterFlow(UProcedureFlowComponent* InComponent)
{
	if (!IsValid(InComponent) || !InComponent->FlowTag.IsValid())
	{
		DLOG(DLogProcedure, Error, TEXT("ProcedureFlowComponent / FlowTag Is NULL"))
		return;
	}

	if (ProcedureFlowComponents.Contains(InComponent))
	{
		DLOG(DLogProcedure, Warning, TEXT("ProcedureFlowComponent Already Register"))
		return;
	}

	ProcedureFlowComponents.Add(InComponent);
	IProcedureFlowInterface::Execute_OnProcedureFlowRegister(InComponent);
	BROADCAST_MANAGER_DELEGATE(Delegate_OnProcedureFlowRegister, BPDelegate_OnProcedureFlowRegister, InComponent)
}

void UProcedureFlowManager::UnRegisterFlow(UProcedureFlowComponent* InComponent)
{
	if (!IsValid(InComponent) || !InComponent->FlowTag.IsValid())
	{
		DLOG(DLogProcedure, Error, TEXT("ProcedureFlowComponent / FlowTag Is NULL"))
		return;
	}

	if (!ProcedureFlowComponents.Contains(InComponent))
	{
		DLOG(DLogProcedure, Warning, TEXT("ProcedureFlowComponent Is Not Register"))
		return;
	}

	ProcedureFlowComponents.Remove(InComponent);
	IProcedureFlowInterface::Execute_OnProcedureFlowUnRegister(InComponent);
	BROADCAST_MANAGER_DELEGATE(Delegate_OnProcedureFlowRegister, BPDelegate_OnProcedureFlowRegister, InComponent)
}

void UProcedureFlowManager::EnterProcedureFlow(FGameplayTag InFlowTag)
{
	if (!InFlowTag.IsValid())
	{
		DLOG(DLogProcedure, Error, TEXT("FlowTag Is NULL"))
		return;
	}

	if (CurrentFlowTag != InFlowTag)
	{
		/* Exit Current Procedure Flow */
		if (CurrentFlowTag.IsValid())
		{
			IProcedureFlowInterface::Execute_OnProcedureFlowExit(GetProcedureFlowComponent(CurrentFlowTag));
			BROADCAST_MANAGER_DELEGATE(Delegate_OnProcedureFlowExit, BPDelegate_OnProcedureFlowExit, GetProcedureFlowComponent(InFlowTag))
		}

		CurrentFlowTag = InFlowTag;

		IProcedureFlowInterface::Execute_OnProcedureFlowEnter(GetProcedureFlowComponent(CurrentFlowTag));
		BROADCAST_MANAGER_DELEGATE(Delegate_OnProcedureFlowEnter, BPDelegate_OnProcedureFlowEnter, GetProcedureFlowComponent(InFlowTag))
	}
}

void UProcedureFlowManager::RefreshCurrentProcedureFlow()
{
	IProcedureFlowInterface::Execute_ReInitProcedureFlow(GetProcedureFlowComponent(CurrentFlowTag));
}

FGameplayTag UProcedureFlowManager::GetCurrentFlowTag() const
{
	return CurrentFlowTag;
}

UProcedureFlowComponent* UProcedureFlowManager::GetCurrentProcedureFlowComponent()
{
	return GetProcedureFlowComponent(GetCurrentFlowTag());
}

UProcedureFlowComponent* UProcedureFlowManager::GetProcedureFlowComponent(FGameplayTag InFlowTag)
{
	if (!InFlowTag.IsValid())
	{
		DLOG(DLogProcedure, Error, TEXT("FlowTag Is NULL"))
		return nullptr;
	}

	for (const auto& ProcedureFlowComponent : ProcedureFlowComponents)
	{
		if (ProcedureFlowComponent->FlowTag == InFlowTag)
		{
			return ProcedureFlowComponent;
		}
	}

	return nullptr;
}

TArray<UProcedureFlowComponent*> UProcedureFlowManager::GetProcedureFlowComponents()
{
	return ProcedureFlowComponents;
}

void UProcedureFlowManager::SortProcedureFlowComponentsAsInitialize()
{
	ProcedureFlowComponents.Sort([](const UProcedureFlowComponent& A, const UProcedureFlowComponent& B)
		{
			return A.ProcedureFlowInitializedOrder > B.ProcedureFlowInitializedOrder;
		}
	);
}

void UProcedureFlowManager::SortProcedureFlowComponentsAsDeinitialize()
{
	ProcedureFlowComponents.Sort([](const UProcedureFlowComponent& A, const UProcedureFlowComponent& B)
		{
			return A.ProcedureFlowDeinitializeOrder > B.ProcedureFlowDeinitializeOrder;
		}
	);
}

void UProcedureFlowManager::Execute(const TFunctionRef<void(UProcedureFlowComponent* InComponent)>& Func)
{
	for (const auto& ProcedureFlowComponent : ProcedureFlowComponents)
	{
		Func(ProcedureFlowComponent);
	}
}
