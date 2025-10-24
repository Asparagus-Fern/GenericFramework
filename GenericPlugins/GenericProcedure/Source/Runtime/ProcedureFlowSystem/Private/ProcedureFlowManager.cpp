// Copyright ChenTaiye 2025. All Rights Reserved.


#include "ProcedureFlowManager.h"

#include "ProcedureFlowActor.h"
#include "ProcedureFlowComponent.h"
#include "ProcedureFlowSettings.h"
#include "ProcedureFlowType.h"

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


void UProcedureFlowManager::HandleOnWorldBeginPlay(UWorld* InWorld)
{
	FManagerInterface::HandleOnWorldBeginPlay(InWorld);

	/* After Procedure Component BeginPlay, Sort Components And Initialize, Then Enter The Setting Default Procedure FLow Tag*/

	SortProcedureFlowComponentsAsInitialize();
	Execute([](UProcedureFlowComponent* Component)
		{
			IProcedureFlowInterface::Execute_OnProcedureFlowInitialized(Component);
		}
	);

	if (UProcedureFlowSettings::Get()->AutoEnterDefaultProcedureFlow)
	{
		if (const UProcedureFlowComponent* FirstProcedureFlow = GetProcedureFlowComponent(UProcedureFlowSettings::Get()->DefaultProcedureFlowTag))
		{
			EnterProcedureFlow(FirstProcedureFlow->ProcedureFlowTag);
		}
	}
}

void UProcedureFlowManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FManagerInterface::HandleOnWorldEndPlay(InWorld);

	SortProcedureFlowComponentsAsDeinitialize();
	Execute([](UProcedureFlowComponent* Component)
		{
			IProcedureFlowInterface::Execute_OnProcedureFlowDeinitialize(Component);
		}
	);
}

void UProcedureFlowManager::RegisterProcedureFlow(const AProcedureFlowActor* InActor)
{
	if (!IsValid(InActor))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowActor Is NULL"))
		return;
	}

	RegisterProcedureFlow(InActor->ProcedureFlowComponent);
}

void UProcedureFlowManager::RegisterProcedureFlow(UProcedureFlowComponent* InComponent)
{
	if (!IsValid(InComponent) || !InComponent->ProcedureFlowTag.IsValid())
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowComponent / FlowTag Is NULL"))
		return;
	}

	if (ProcedureFlowComponents.Contains(InComponent))
	{
		GenericLOG(GenericLogProcedureFlow, Warning, TEXT("ProcedureFlowComponent Already Register"))
		return;
	}

	ProcedureFlowComponents.Add(InComponent);
	IProcedureFlowInterface::Execute_OnProcedureFlowRegister(InComponent);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnProcedureFlowRegister, BPDelegate_OnProcedureFlowRegister, InComponent)
}

void UProcedureFlowManager::UnRegisterProcedureFlow(const AProcedureFlowActor* InActor)
{
	if (!IsValid(InActor))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowActor Is NULL"))
		return;
	}

	UnRegisterProcedureFlow(InActor->ProcedureFlowComponent);
}

void UProcedureFlowManager::UnRegisterProcedureFlow(UProcedureFlowComponent* InComponent)
{
	if (!IsValid(InComponent) || !InComponent->ProcedureFlowTag.IsValid())
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowComponent / FlowTag Is NULL"))
		return;
	}

	if (!ProcedureFlowComponents.Contains(InComponent))
	{
		GenericLOG(GenericLogProcedureFlow, Warning, TEXT("ProcedureFlowComponent Is Not Register"))
		return;
	}

	ProcedureFlowComponents.Remove(InComponent);
	IProcedureFlowInterface::Execute_OnProcedureFlowUnRegister(InComponent);
	BROADCAST_UNIFIED_DELEGATE(Delegate_OnProcedureFlowRegister, BPDelegate_OnProcedureFlowRegister, InComponent)
}

void UProcedureFlowManager::EnterProcedureFlow(const AProcedureFlowActor* InActor)
{
	if (!IsValid(InActor))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowActor Is NULL"))
		return;
	}

	EnterProcedureFlow(InActor->ProcedureFlowComponent);
}

void UProcedureFlowManager::EnterProcedureFlow(const UProcedureFlowComponent* InComponent)
{
	if (!IsValid(InComponent))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowComponent Is NULL"))
		return;
	}

	EnterProcedureFlow(InComponent->ProcedureFlowTag);
}

void UProcedureFlowManager::EnterProcedureFlow(FGameplayTag InProcedureFlowTag)
{
	if (!InProcedureFlowTag.IsValid())
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("FlowTag Is NULL"))
		return;
	}

	if (CurrentProcedureFlowTag != InProcedureFlowTag)
	{
		ExitProcedureFlow(CurrentProcedureFlowTag);
		CurrentProcedureFlowTag = InProcedureFlowTag;

		IProcedureFlowInterface::Execute_OnProcedureFlowEnter(GetProcedureFlowComponent(CurrentProcedureFlowTag));
		BROADCAST_UNIFIED_DELEGATE(Delegate_OnProcedureFlowEnter, BPDelegate_OnProcedureFlowEnter, GetProcedureFlowComponent(InProcedureFlowTag))
	}
}

void UProcedureFlowManager::RefreshCurrentProcedureFlow()
{
	IProcedureFlowInterface::Execute_ReInitProcedureFlow(GetProcedureFlowComponent(CurrentProcedureFlowTag));
}

void UProcedureFlowManager::ReEnterCurrentProcedureFlow()
{
	const FGameplayTag ReEnterTag = GetCurrentProcedureFlowTag();
	ExitProcedureFlow(ReEnterTag);
	EnterProcedureFlow(ReEnterTag);
}

void UProcedureFlowManager::ExitProcedureFlow(const AProcedureFlowActor* InActor)
{
	if (!IsValid(InActor))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowActor Is NULL"))
		return;
	}

	ExitProcedureFlow(InActor->ProcedureFlowComponent);
}

void UProcedureFlowManager::ExitProcedureFlow(const UProcedureFlowComponent* InComponent)
{
	if (!IsValid(InComponent))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowComponent Is NULL"))
		return;
	}

	ExitProcedureFlow(InComponent->ProcedureFlowTag);
}

void UProcedureFlowManager::ExitProcedureFlow(FGameplayTag InProcedureFlowTag)
{
	if (!InProcedureFlowTag.IsValid())
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("FlowTag Is NULL"))
		return;
	}

	if (CurrentProcedureFlowTag == InProcedureFlowTag)
	{
		IProcedureFlowInterface::Execute_OnProcedureFlowExit(GetProcedureFlowComponent(CurrentProcedureFlowTag));
		BROADCAST_UNIFIED_DELEGATE(Delegate_OnProcedureFlowExit, BPDelegate_OnProcedureFlowExit, GetProcedureFlowComponent(InProcedureFlowTag))

		CurrentProcedureFlowTag = FGameplayTag::EmptyTag;
	}
}

bool UProcedureFlowManager::IsProcedureFlowActived(const AProcedureFlowActor* InActor) const
{
	if (!IsValid(InActor))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowActor Is NULL"))
		return false;
	}

	return IsProcedureFlowActived(InActor->ProcedureFlowComponent);
}

bool UProcedureFlowManager::IsProcedureFlowActived(const UProcedureFlowComponent* InComponent) const
{
	if (!IsValid(InComponent))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowComponent Is NULL"))
		return false;
	}

	return IsProcedureFlowActived(InComponent->ProcedureFlowTag);
}

bool UProcedureFlowManager::IsProcedureFlowActived(FGameplayTag InProcedureFlowTag) const
{
	return InProcedureFlowTag.IsValid() && InProcedureFlowTag == CurrentProcedureFlowTag;
}

FGameplayTag UProcedureFlowManager::GetCurrentProcedureFlowTag() const
{
	return CurrentProcedureFlowTag;
}

UProcedureFlowComponent* UProcedureFlowManager::GetCurrentProcedureFlowComponent()
{
	return GetProcedureFlowComponent(GetCurrentProcedureFlowTag());
}

TArray<UProcedureFlowComponent*> UProcedureFlowManager::GetProcedureFlowComponents()
{
	return ProcedureFlowComponents;
}

UProcedureFlowComponent* UProcedureFlowManager::GetProcedureFlowComponent(FGameplayTag InProcedureFlowTag)
{
	if (!InProcedureFlowTag.IsValid())
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("FlowTag Is NULL"))
		return nullptr;
	}

	for (const auto& ProcedureFlowComponent : ProcedureFlowComponents)
	{
		if (ProcedureFlowComponent->ProcedureFlowTag == InProcedureFlowTag)
		{
			return ProcedureFlowComponent;
		}
	}

	return nullptr;
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
