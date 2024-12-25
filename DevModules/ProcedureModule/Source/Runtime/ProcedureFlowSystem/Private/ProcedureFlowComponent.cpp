// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcedureFlowComponent.h"

#include "ProcedureFlowManager.h"
#include "Manager/ManagerStatics.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedureFlow, "Procedure.Flow");

UProcedureFlowComponent::UProcedureFlowComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UProcedureFlowComponent::BeginPlay()
{
	Super::BeginPlay();

	if (UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
	{
		ProcedureFlowManager->RegisterFlow(this);
	}
}

void UProcedureFlowComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
	{
		ProcedureFlowManager->UnRegisterFlow(this);
	}

	Super::EndPlay(EndPlayReason);
}
