// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions_ProcedureFlow.h"

#include "ProcedureFlowActor.h"
#include "ProcedureFlowComponent.h"
#include "ProcedureFlowManager.h"
#include "Manager/ManagerStatics.h"

void UBPFunctions_ProcedureFlow::RegisterProcedureFlowByActor(AProcedureFlowActor* InActor)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		ProcedureFlowManager->RegisterProcedureFlow(InActor);
	}
}

void UBPFunctions_ProcedureFlow::RegisterProcedureFlowByComponent(UProcedureFlowComponent* InComponent)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		ProcedureFlowManager->RegisterProcedureFlow(InComponent);
	}
}

void UBPFunctions_ProcedureFlow::EnterProcedureFlowByActor(AProcedureFlowActor* InActor)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		ProcedureFlowManager->EnterProcedureFlow(InActor);
	}
}

void UBPFunctions_ProcedureFlow::EnterProcedureFlowByComponent(UProcedureFlowComponent* InComponent)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		ProcedureFlowManager->EnterProcedureFlow(InComponent);
	}
}

void UBPFunctions_ProcedureFlow::EnterProcedureFlowByTag(FGameplayTag InProcedureFlowTag)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		ProcedureFlowManager->EnterProcedureFlow(InProcedureFlowTag);
	}
}

void UBPFunctions_ProcedureFlow::RefreshCurrentProcedureFlow()
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		ProcedureFlowManager->RefreshCurrentProcedureFlow();
	}
}

void UBPFunctions_ProcedureFlow::ReEnterCurrentProcedureFlow()
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		ProcedureFlowManager->ReEnterCurrentProcedureFlow();
	}
}

void UBPFunctions_ProcedureFlow::ExitProcedureFlowByActor(AProcedureFlowActor* InActor)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		ProcedureFlowManager->ExitProcedureFlow(InActor);
	}
}

void UBPFunctions_ProcedureFlow::ExitProcedureFlowByComponent(UProcedureFlowComponent* InComponent)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		ProcedureFlowManager->ExitProcedureFlow(InComponent);
	}
}

void UBPFunctions_ProcedureFlow::ExitProcedureFlowByTag(FGameplayTag InProcedureFlowTag)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		ProcedureFlowManager->ExitProcedureFlow(InProcedureFlowTag);
	}
}

void UBPFunctions_ProcedureFlow::UnRegisterProcedureFlowByActor(AProcedureFlowActor* InActor)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		ProcedureFlowManager->UnRegisterProcedureFlow(InActor);
	}
}

void UBPFunctions_ProcedureFlow::UnRegisterProcedureFlowByComponent(UProcedureFlowComponent* InComponent)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		ProcedureFlowManager->UnRegisterProcedureFlow(InComponent);
	}
}

bool UBPFunctions_ProcedureFlow::IsProcedureFlowActorActived(const AProcedureFlowActor* InActor)
{
	if (const UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		return ProcedureFlowManager->IsProcedureFlowActived(InActor);
	}

	return false;
}

bool UBPFunctions_ProcedureFlow::IsProcedureFlowComponentActived(const UProcedureFlowComponent* InComponent)
{
	if (const UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		return ProcedureFlowManager->IsProcedureFlowActived(InComponent);
	}

	return false;
}

bool UBPFunctions_ProcedureFlow::IsProcedureFlowActived(FGameplayTag InProcedureFlowTag)
{
	if (const UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		return ProcedureFlowManager->IsProcedureFlowActived(InProcedureFlowTag);
	}

	return false;
}

FGameplayTag UBPFunctions_ProcedureFlow::GetCurrentProcedureFlowTag()
{
	if (const UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		return ProcedureFlowManager->GetCurrentProcedureFlowTag();
	}

	return FGameplayTag::EmptyTag;
}

UProcedureFlowComponent* UBPFunctions_ProcedureFlow::GetCurrentProcedureFlowComponent()
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		return ProcedureFlowManager->GetCurrentProcedureFlowComponent();
	}

	return nullptr;
}

UProcedureFlowComponent* UBPFunctions_ProcedureFlow::GetCurrentProcedureFlowComponentByClass(const TSubclassOf<UProcedureFlowComponent> InClass)
{
	ensure(InClass);

	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		return ProcedureFlowManager->GetCurrentProcedureFlowComponent<UProcedureFlowComponent>();
	}

	return nullptr;
}

UProcedureFlowComponent* UBPFunctions_ProcedureFlow::GetProcedureFlowComponent(FGameplayTag InProcedureFlowTag)
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		return ProcedureFlowManager->GetProcedureFlowComponent(InProcedureFlowTag);
	}

	return nullptr;
}

UProcedureFlowComponent* UBPFunctions_ProcedureFlow::GetProcedureFlowComponentByClass(FGameplayTag InProcedureFlowTag, const TSubclassOf<UProcedureFlowComponent> InClass)
{
	ensure(InClass);

	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		return ProcedureFlowManager->GetProcedureFlowComponent<UProcedureFlowComponent>(InProcedureFlowTag);
	}

	return nullptr;
}

TArray<UProcedureFlowComponent*> UBPFunctions_ProcedureFlow::GetProcedureFlowComponents()
{
	if (UProcedureFlowManager* ProcedureFlowManager = GetManagerOwner<UProcedureFlowManager>())
	{
		return ProcedureFlowManager->GetProcedureFlowComponents();
	}

	return TArray<UProcedureFlowComponent*>{};
}
