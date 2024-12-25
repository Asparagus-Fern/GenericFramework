// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcedureFlowManager.h"

#include "ProcedureFlowComponent.h"

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
}
