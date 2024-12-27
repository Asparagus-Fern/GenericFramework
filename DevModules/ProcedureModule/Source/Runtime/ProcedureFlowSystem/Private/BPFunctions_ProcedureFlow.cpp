// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions_ProcedureFlow.h"

#include "ProcedureFlowActor.h"
#include "ProcedureFlowComponent.h"
#include "ProcedureFlowManager.h"
#include "Manager/ManagerStatics.h"

void UBPFunctions_ProcedureFlow::RegisterFlowByActor(AProcedureFlowActor* InActor)
{
	RegisterFlowByComponent(InActor->ProcedureFlowComponent);
}

void UBPFunctions_ProcedureFlow::RegisterFlowByComponent(UProcedureFlowComponent* InComponent)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
	{
		ProcedureFlowManager->RegisterFlow(InComponent);
	}
}

void UBPFunctions_ProcedureFlow::EnterProcedureFlowByActor(AProcedureFlowActor* InActor)
{
	EnterProcedureFlowByComponent(InActor->ProcedureFlowComponent);
}

void UBPFunctions_ProcedureFlow::EnterProcedureFlowByComponent(UProcedureFlowComponent* InComponent)
{
	EnterProcedureFlowByTag(InComponent->FlowTag);
}

void UBPFunctions_ProcedureFlow::EnterProcedureFlowByTag(FGameplayTag InFlowTag)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
	{
		ProcedureFlowManager->EnterProcedureFlow(InFlowTag);
	}
}

void UBPFunctions_ProcedureFlow::UnRegisterFlowByActor(AProcedureFlowActor* InActor)
{
	UnRegisterFlowByComponent(InActor->ProcedureFlowComponent);
}

void UBPFunctions_ProcedureFlow::UnRegisterFlowByComponent(UProcedureFlowComponent* InComponent)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
	{
		ProcedureFlowManager->UnRegisterFlow(InComponent);
	}
}

FGameplayTag UBPFunctions_ProcedureFlow::GetCurrentFlowTag()
{
	if (const UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
	{
		return ProcedureFlowManager->GetCurrentFlowTag();
	}

	return FGameplayTag::EmptyTag;
}

UProcedureFlowComponent* UBPFunctions_ProcedureFlow::GetCurrentProcedureFlowComponent()
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
	{
		return ProcedureFlowManager->GetCurrentProcedureFlowComponent();
	}

	return nullptr;
}

UProcedureFlowComponent* UBPFunctions_ProcedureFlow::GetProcedureFlowComponent(FGameplayTag InFlowTag)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
	{
		return ProcedureFlowManager->GetProcedureFlowComponent(InFlowTag);
	}

	return nullptr;
}

TArray<UProcedureFlowComponent*> UBPFunctions_ProcedureFlow::GetProcedureFlowComponents()
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
	{
		return ProcedureFlowManager->GetProcedureFlowComponents();
	}

	return TArray<UProcedureFlowComponent*>{};
}
