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

	if (ProcedureFlowTag.IsValid() && !bManualRegister && (bRegisterEvenIsHidden || (!bRegisterEvenIsHidden && !GetOwner()->IsHidden())))
	{
		if (UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
		{
			ProcedureFlowManager->RegisterProcedureFlow(this);
		}
	}
}

void UProcedureFlowComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ProcedureFlowTag.IsValid())
	{
		if (UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
		{
			ProcedureFlowManager->UnRegisterProcedureFlow(this);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void UProcedureFlowComponent::OnProcedureFlowRegister_Implementation()
{
	IProcedureFlowInterface::OnProcedureFlowRegister_Implementation();

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowRegister(GetOwner());
	}
}

void UProcedureFlowComponent::OnProcedureFlowInitialized_Implementation()
{
	IProcedureFlowInterface::OnProcedureFlowInitialized_Implementation();

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowInitialized(GetOwner());
	}
}

void UProcedureFlowComponent::OnProcedureFlowEnter_Implementation()
{
	IProcedureFlowInterface::OnProcedureFlowEnter_Implementation();

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowEnter(GetOwner());
	}
}

void UProcedureFlowComponent::ReInitProcedureFlow_Implementation()
{
	IProcedureFlowInterface::ReInitProcedureFlow_Implementation();

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_ReInitProcedureFlow(GetOwner());
	}
}

void UProcedureFlowComponent::OnProcedureFlowExit_Implementation()
{
	IProcedureFlowInterface::OnProcedureFlowExit_Implementation();

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowExit(GetOwner());
	}
}

void UProcedureFlowComponent::OnProcedureFlowDeinitialize_Implementation()
{
	IProcedureFlowInterface::OnProcedureFlowDeinitialize_Implementation();

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowDeinitialize(GetOwner());
	}
}

void UProcedureFlowComponent::OnProcedureFlowUnRegister_Implementation()
{
	IProcedureFlowInterface::OnProcedureFlowUnRegister_Implementation();

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowUnRegister(GetOwner());
	}
}
