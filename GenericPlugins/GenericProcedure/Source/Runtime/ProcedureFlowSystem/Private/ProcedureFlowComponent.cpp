// Copyright ChenTaiye 2025. All Rights Reserved.


#include "ProcedureFlowComponent.h"

#include "ProcedureFlowExecute.h"
#include "ProcedureFlowManager.h"
#include "Manager/ManagerStatics.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedureFlow, "Procedure.Flow");

void UProcedureFlowComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ProcedureFlowTag.IsValid() && !bManualRegister && (bRegisterEvenIsHidden || (!bRegisterEvenIsHidden && !GetOwner()->IsHidden())))
	{
		if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
		{
			ProcedureFlowManager->RegisterProcedureFlow(this);
		}
	}
}

void UProcedureFlowComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (ProcedureFlowTag.IsValid())
	{
		if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
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

	for (auto& ProcedureFlowExecute : ProcedureFlowExecutes)
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowRegister(ProcedureFlowExecute);
	}
}

void UProcedureFlowComponent::OnProcedureFlowInitialized_Implementation()
{
	IProcedureFlowInterface::OnProcedureFlowInitialized_Implementation();

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowInitialized(GetOwner());
	}

	for (auto& ProcedureFlowExecute : ProcedureFlowExecutes)
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowInitialized(ProcedureFlowExecute);
	}
}

void UProcedureFlowComponent::OnProcedureFlowEnter_Implementation()
{
	IProcedureFlowInterface::OnProcedureFlowEnter_Implementation();

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowEnter(GetOwner());
	}

	for (auto& ProcedureFlowExecute : ProcedureFlowExecutes)
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowEnter(ProcedureFlowExecute);
	}
}

void UProcedureFlowComponent::ReInitProcedureFlow_Implementation()
{
	IProcedureFlowInterface::ReInitProcedureFlow_Implementation();

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_ReInitProcedureFlow(GetOwner());
	}

	for (auto& ProcedureFlowExecute : ProcedureFlowExecutes)
	{
		IProcedureFlowInterface::Execute_ReInitProcedureFlow(ProcedureFlowExecute);
	}
}

void UProcedureFlowComponent::OnProcedureFlowExit_Implementation()
{
	IProcedureFlowInterface::OnProcedureFlowExit_Implementation();

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowExit(GetOwner());
	}

	for (auto& ProcedureFlowExecute : ProcedureFlowExecutes)
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowExit(ProcedureFlowExecute);
	}
}

void UProcedureFlowComponent::OnProcedureFlowDeinitialize_Implementation()
{
	IProcedureFlowInterface::OnProcedureFlowDeinitialize_Implementation();

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowDeinitialize(GetOwner());
	}

	for (auto& ProcedureFlowExecute : ProcedureFlowExecutes)
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowDeinitialize(ProcedureFlowExecute);
	}
}

void UProcedureFlowComponent::OnProcedureFlowUnRegister_Implementation()
{
	IProcedureFlowInterface::OnProcedureFlowUnRegister_Implementation();

	if (GetOwner()->GetClass()->ImplementsInterface(UProcedureFlowInterface::StaticClass()))
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowUnRegister(GetOwner());
	}

	for (auto& ProcedureFlowExecute : ProcedureFlowExecutes)
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowUnRegister(ProcedureFlowExecute);
	}
}
