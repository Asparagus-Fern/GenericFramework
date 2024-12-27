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
	
	if (FlowTag.IsValid() && !bManualRegister && (bRegisterEvenIsHidden || (!bRegisterEvenIsHidden && !GetOwner()->IsHidden())))
	{
		if (UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
		{
			ProcedureFlowManager->RegisterFlow(this);
		}
	}
}

void UProcedureFlowComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (FlowTag.IsValid())
	{
		if (UProcedureFlowManager* ProcedureFlowManager = GetManager<UProcedureFlowManager>())
		{
			ProcedureFlowManager->UnRegisterFlow(this);
		}
	}

	Super::EndPlay(EndPlayReason);
}

void UProcedureFlowComponent::OnProcedureFlowRegister_Implementation(UProcedureFlowComponent* InProcedureFlow)
{
	IProcedureFlowInterface::OnProcedureFlowRegister_Implementation(InProcedureFlow);

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowRegister(GetOwner(), InProcedureFlow);
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

void UProcedureFlowComponent::PreProcedureFlowEnter_Implementation(UProcedureFlowComponent* InProcedureFlow)
{
	IProcedureFlowInterface::PreProcedureFlowEnter_Implementation(InProcedureFlow);

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_PreProcedureFlowEnter(GetOwner(), InProcedureFlow);
	}
}

void UProcedureFlowComponent::OnProcedureFlowEnter_Implementation(UProcedureFlowComponent* InProcedureFlow)
{
	IProcedureFlowInterface::OnProcedureFlowEnter_Implementation(InProcedureFlow);

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowEnter(GetOwner(), InProcedureFlow);
	}
}

void UProcedureFlowComponent::PostProcedureFlowEnter_Implementation(UProcedureFlowComponent* InProcedureFlow)
{
	IProcedureFlowInterface::PostProcedureFlowEnter_Implementation(InProcedureFlow);

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_PostProcedureFlowEnter(GetOwner(), InProcedureFlow);
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

void UProcedureFlowComponent::PreProcedureFlowExit_Implementation(UProcedureFlowComponent* InProcedureFlow)
{
	IProcedureFlowInterface::PreProcedureFlowExit_Implementation(InProcedureFlow);

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_PreProcedureFlowExit(GetOwner(), InProcedureFlow);
	}
}

void UProcedureFlowComponent::OnProcedureFlowExit_Implementation(UProcedureFlowComponent* InProcedureFlow)
{
	IProcedureFlowInterface::OnProcedureFlowExit_Implementation(InProcedureFlow);

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowExit(GetOwner(), InProcedureFlow);
	}
}

void UProcedureFlowComponent::PostProcedureFlowExit_Implementation(UProcedureFlowComponent* InProcedureFlow)
{
	IProcedureFlowInterface::PostProcedureFlowExit_Implementation(InProcedureFlow);

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_PostProcedureFlowExit(GetOwner(), InProcedureFlow);
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

void UProcedureFlowComponent::OnProcedureFlowUnRegister_Implementation(UProcedureFlowComponent* InProcedureFlow)
{
	IProcedureFlowInterface::OnProcedureFlowUnRegister_Implementation(InProcedureFlow);

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowUnRegister(GetOwner(), InProcedureFlow);
	}
}
