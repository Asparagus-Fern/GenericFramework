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

	if (const UProcedureFlowComponent* FirstProcedureFlow = GetProcedureFlowComponent(UProcedureFlowSetting::Get()->DefaultFlowTag))
	{
		EnterProcedureFlow(FirstProcedureFlow->FlowTag);
	}
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
	Execute([](UProcedureFlowComponent* Component)
		{
			IProcedureFlowInterface::Execute_OnFlowRegister(Component, Component);
		}
	);
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
	Execute([](UProcedureFlowComponent* Component)
		{
			IProcedureFlowInterface::Execute_OnFlowUnRegister(Component, Component);
		}
	);
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
			SortProcedureFlowComponentsAsExit();
			Execute([](UProcedureFlowComponent* InComponent)
				{
				}
			);
		}
	}
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

void UProcedureFlowManager::SortProcedureFlowComponentsAsEnter()
{
	ProcedureFlowComponents.Sort([](const UProcedureFlowComponent& A, const UProcedureFlowComponent& B)
		{
			return A.ProcedureFlowInOrder > B.ProcedureFlowInOrder;
		}
	);
}

void UProcedureFlowManager::SortProcedureFlowComponentsAsExit()
{
	ProcedureFlowComponents.Sort([](const UProcedureFlowComponent& A, const UProcedureFlowComponent& B)
		{
			return A.ProcedureFlowOutOrder > B.ProcedureFlowOutOrder;
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
