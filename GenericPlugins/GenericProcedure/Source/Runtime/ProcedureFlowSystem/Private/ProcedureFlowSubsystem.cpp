// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ProcedureFlowSubsystem.h"

#include "ProcedureFlowActor.h"
#include "ProcedureFlowComponent.h"
#include "ProcedureFlowSettings.h"
#include "ProcedureFlowType.h"
#include "Type/DebugType.h"
#include "Type/GenericType.h"

UProcedureFlowSubsystem* UProcedureFlowSubsystem::Get(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetSubsystem<ThisClass>();
	}
	return nullptr;
}

void UProcedureFlowSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UProcedureFlowComponent::OnRegister.AddUObject(this, &UProcedureFlowSubsystem::RegisterProcedureFlow);
	UProcedureFlowComponent::OnUnRegister.AddUObject(this, &UProcedureFlowSubsystem::UnRegisterProcedureFlow);
}

void UProcedureFlowSubsystem::OnWorldMatchStarting()
{
	Super::OnWorldMatchStarting();

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

void UProcedureFlowSubsystem::OnWorldBeginTearDown(UWorld* InWorld)
{
	Super::OnWorldBeginTearDown(InWorld);

	SortProcedureFlowComponentsAsDeinitialize();
	Execute([](UProcedureFlowComponent* Component)
		{
			IProcedureFlowInterface::Execute_OnProcedureFlowDeinitialize(Component);
		}
	);
}

void UProcedureFlowSubsystem::Deinitialize()
{
	Super::Deinitialize();

	UProcedureFlowComponent::OnRegister.RemoveAll(this);
	UProcedureFlowComponent::OnUnRegister.RemoveAll(this);
}

void UProcedureFlowSubsystem::RegisterProcedureFlow(const AProcedureFlowActor* InActor)
{
	if (!IsValid(InActor))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowActor Is NULL"))
		return;
	}

	RegisterProcedureFlow(InActor->ProcedureFlowComponent);
}

void UProcedureFlowSubsystem::RegisterProcedureFlow(UProcedureFlowComponent* InComponent)
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

void UProcedureFlowSubsystem::UnRegisterProcedureFlow(const AProcedureFlowActor* InActor)
{
	if (!IsValid(InActor))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowActor Is NULL"))
		return;
	}

	UnRegisterProcedureFlow(InActor->ProcedureFlowComponent);
}

void UProcedureFlowSubsystem::UnRegisterProcedureFlow(UProcedureFlowComponent* InComponent)
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

void UProcedureFlowSubsystem::EnterProcedureFlow(const AProcedureFlowActor* InActor)
{
	if (!IsValid(InActor))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowActor Is NULL"))
		return;
	}

	EnterProcedureFlow(InActor->ProcedureFlowComponent);
}

void UProcedureFlowSubsystem::EnterProcedureFlow(const UProcedureFlowComponent* InComponent)
{
	if (!IsValid(InComponent))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowComponent Is NULL"))
		return;
	}

	EnterProcedureFlow(InComponent->ProcedureFlowTag);
}

void UProcedureFlowSubsystem::EnterProcedureFlow(FGameplayTag InProcedureFlowTag)
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

void UProcedureFlowSubsystem::RefreshCurrentProcedureFlow()
{
	IProcedureFlowInterface::Execute_ReInitProcedureFlow(GetProcedureFlowComponent(CurrentProcedureFlowTag));
}

void UProcedureFlowSubsystem::ReEnterCurrentProcedureFlow()
{
	const FGameplayTag ReEnterTag = GetCurrentProcedureFlowTag();
	ExitProcedureFlow(ReEnterTag);
	EnterProcedureFlow(ReEnterTag);
}

void UProcedureFlowSubsystem::ExitProcedureFlow(const AProcedureFlowActor* InActor)
{
	if (!IsValid(InActor))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowActor Is NULL"))
		return;
	}

	ExitProcedureFlow(InActor->ProcedureFlowComponent);
}

void UProcedureFlowSubsystem::ExitProcedureFlow(const UProcedureFlowComponent* InComponent)
{
	if (!IsValid(InComponent))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowComponent Is NULL"))
		return;
	}

	ExitProcedureFlow(InComponent->ProcedureFlowTag);
}

void UProcedureFlowSubsystem::ExitProcedureFlow(FGameplayTag InProcedureFlowTag)
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

bool UProcedureFlowSubsystem::IsProcedureFlowActived(const AProcedureFlowActor* InActor) const
{
	if (!IsValid(InActor))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowActor Is NULL"))
		return false;
	}

	return IsProcedureFlowActived(InActor->ProcedureFlowComponent);
}

bool UProcedureFlowSubsystem::IsProcedureFlowActived(const UProcedureFlowComponent* InComponent) const
{
	if (!IsValid(InComponent))
	{
		GenericLOG(GenericLogProcedureFlow, Error, TEXT("ProcedureFlowComponent Is NULL"))
		return false;
	}

	return IsProcedureFlowActived(InComponent->ProcedureFlowTag);
}

bool UProcedureFlowSubsystem::IsProcedureFlowActived(FGameplayTag InProcedureFlowTag) const
{
	return InProcedureFlowTag.IsValid() && InProcedureFlowTag == CurrentProcedureFlowTag;
}

FGameplayTag UProcedureFlowSubsystem::GetCurrentProcedureFlowTag() const
{
	return CurrentProcedureFlowTag;
}

UProcedureFlowComponent* UProcedureFlowSubsystem::GetCurrentProcedureFlowComponent()
{
	return GetProcedureFlowComponent(GetCurrentProcedureFlowTag());
}

TArray<UProcedureFlowComponent*> UProcedureFlowSubsystem::GetProcedureFlowComponents()
{
	return ProcedureFlowComponents;
}

UProcedureFlowComponent* UProcedureFlowSubsystem::GetProcedureFlowComponent(FGameplayTag InProcedureFlowTag)
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

void UProcedureFlowSubsystem::SortProcedureFlowComponentsAsInitialize()
{
	ProcedureFlowComponents.Sort([](const UProcedureFlowComponent& A, const UProcedureFlowComponent& B)
		{
			return A.ProcedureFlowInitializedOrder > B.ProcedureFlowInitializedOrder;
		}
	);
}

void UProcedureFlowSubsystem::SortProcedureFlowComponentsAsDeinitialize()
{
	ProcedureFlowComponents.Sort([](const UProcedureFlowComponent& A, const UProcedureFlowComponent& B)
		{
			return A.ProcedureFlowDeinitializeOrder > B.ProcedureFlowDeinitializeOrder;
		}
	);
}

void UProcedureFlowSubsystem::Execute(const TFunctionRef<void(UProcedureFlowComponent* InComponent)>& Func)
{
	for (const auto& ProcedureFlowComponent : ProcedureFlowComponents)
	{
		Func(ProcedureFlowComponent);
	}
}
