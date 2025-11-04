// Copyright ChenTaiye 2025. All Rights Reserved.

#include "BPFunctions_ProcedureFlow.h"

#include "ProcedureFlowComponent.h"
#include "ProcedureFlowSubsystem.h"

void UBPFunctions_ProcedureFlow::RegisterProcedureFlowByActor(const UObject* WorldContextObject, AProcedureFlowActor* InActor)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		ProcedureFlowSubsystem->RegisterProcedureFlow(InActor);
	}
}

void UBPFunctions_ProcedureFlow::RegisterProcedureFlowByComponent(const UObject* WorldContextObject, UProcedureFlowComponent* InComponent)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		ProcedureFlowSubsystem->RegisterProcedureFlow(InComponent);
	}
}

void UBPFunctions_ProcedureFlow::EnterProcedureFlowByActor(const UObject* WorldContextObject, AProcedureFlowActor* InActor)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		ProcedureFlowSubsystem->EnterProcedureFlow(InActor);
	}
}

void UBPFunctions_ProcedureFlow::EnterProcedureFlowByComponent(const UObject* WorldContextObject, UProcedureFlowComponent* InComponent)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		ProcedureFlowSubsystem->EnterProcedureFlow(InComponent);
	}
}

void UBPFunctions_ProcedureFlow::EnterProcedureFlowByTag(const UObject* WorldContextObject, FGameplayTag InProcedureFlowTag)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		ProcedureFlowSubsystem->EnterProcedureFlow(InProcedureFlowTag);
	}
}

void UBPFunctions_ProcedureFlow::RefreshCurrentProcedureFlow(const UObject* WorldContextObject)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		ProcedureFlowSubsystem->RefreshCurrentProcedureFlow();
	}
}

void UBPFunctions_ProcedureFlow::ReEnterCurrentProcedureFlow(const UObject* WorldContextObject)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		ProcedureFlowSubsystem->ReEnterCurrentProcedureFlow();
	}
}

void UBPFunctions_ProcedureFlow::ExitProcedureFlowByActor(const UObject* WorldContextObject, AProcedureFlowActor* InActor)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		ProcedureFlowSubsystem->ExitProcedureFlow(InActor);
	}
}

void UBPFunctions_ProcedureFlow::ExitProcedureFlowByComponent(const UObject* WorldContextObject, UProcedureFlowComponent* InComponent)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		ProcedureFlowSubsystem->ExitProcedureFlow(InComponent);
	}
}

void UBPFunctions_ProcedureFlow::ExitProcedureFlowByTag(const UObject* WorldContextObject, FGameplayTag InProcedureFlowTag)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		ProcedureFlowSubsystem->ExitProcedureFlow(InProcedureFlowTag);
	}
}

void UBPFunctions_ProcedureFlow::UnRegisterProcedureFlowByActor(const UObject* WorldContextObject, AProcedureFlowActor* InActor)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		ProcedureFlowSubsystem->UnRegisterProcedureFlow(InActor);
	}
}

void UBPFunctions_ProcedureFlow::UnRegisterProcedureFlowByComponent(const UObject* WorldContextObject, UProcedureFlowComponent* InComponent)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		ProcedureFlowSubsystem->UnRegisterProcedureFlow(InComponent);
	}
}

bool UBPFunctions_ProcedureFlow::IsProcedureFlowActorActived(const UObject* WorldContextObject, const AProcedureFlowActor* InActor)
{
	if (const UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		return ProcedureFlowSubsystem->IsProcedureFlowActived(InActor);
	}

	return false;
}

bool UBPFunctions_ProcedureFlow::IsProcedureFlowComponentActived(const UObject* WorldContextObject, const UProcedureFlowComponent* InComponent)
{
	if (const UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		return ProcedureFlowSubsystem->IsProcedureFlowActived(InComponent);
	}

	return false;
}

bool UBPFunctions_ProcedureFlow::IsProcedureFlowActived(const UObject* WorldContextObject, FGameplayTag InProcedureFlowTag)
{
	if (const UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		return ProcedureFlowSubsystem->IsProcedureFlowActived(InProcedureFlowTag);
	}

	return false;
}

FGameplayTag UBPFunctions_ProcedureFlow::GetCurrentProcedureFlowTag(const UObject* WorldContextObject)
{
	if (const UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		return ProcedureFlowSubsystem->GetCurrentProcedureFlowTag();
	}

	return FGameplayTag::EmptyTag;
}

UProcedureFlowComponent* UBPFunctions_ProcedureFlow::GetCurrentProcedureFlowComponent(const UObject* WorldContextObject)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		return ProcedureFlowSubsystem->GetCurrentProcedureFlowComponent();
	}

	return nullptr;
}

UProcedureFlowComponent* UBPFunctions_ProcedureFlow::GetCurrentProcedureFlowComponentByClass(const UObject* WorldContextObject, const TSubclassOf<UProcedureFlowComponent> InClass)
{
	ensure(InClass);

	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		return ProcedureFlowSubsystem->GetCurrentProcedureFlowComponent<UProcedureFlowComponent>();
	}

	return nullptr;
}

UProcedureFlowComponent* UBPFunctions_ProcedureFlow::GetProcedureFlowComponent(const UObject* WorldContextObject, FGameplayTag InProcedureFlowTag)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		return ProcedureFlowSubsystem->GetProcedureFlowComponent(InProcedureFlowTag);
	}

	return nullptr;
}

UProcedureFlowComponent* UBPFunctions_ProcedureFlow::GetProcedureFlowComponentByClass(const UObject* WorldContextObject, FGameplayTag InProcedureFlowTag, const TSubclassOf<UProcedureFlowComponent> InClass)
{
	ensure(InClass);

	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		return ProcedureFlowSubsystem->GetProcedureFlowComponent<UProcedureFlowComponent>(InProcedureFlowTag);
	}

	return nullptr;
}

TArray<UProcedureFlowComponent*> UBPFunctions_ProcedureFlow::GetProcedureFlowComponents(const UObject* WorldContextObject)
{
	if (UProcedureFlowSubsystem* ProcedureFlowSubsystem = UProcedureFlowSubsystem::Get(WorldContextObject))
	{
		return ProcedureFlowSubsystem->GetProcedureFlowComponents();
	}

	return TArray<UProcedureFlowComponent*>{};
}
