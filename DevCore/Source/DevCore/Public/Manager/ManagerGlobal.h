// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreManager.h"
#include "ManagerSubsystem.h"

template <typename ManagerClass>
static ManagerClass* GetManager()
{
	UCoreManager* Manager = UManagerSubsystem::Get()->GetManager(ManagerClass::StaticClass());
	if (IsValid(Manager))
	{
		return Cast<ManagerClass>(Manager);
	}

	return nullptr;
}

template <typename InterfaceClass>
static TArray<InterfaceClass*> GetManagersWithInterface()
{
	TArray<InterfaceClass*> Managers;
	for (const auto& Manager : UManagerSubsystem::Get()->GetManagers())
	{
		if (Manager->GetClass()->ImplementsInterface(InterfaceClass::UClassType::StaticClass()))
		{
			Managers.Add(Cast<InterfaceClass>(Manager));
		}
	}
	return Managers;
}

/**
 * 
 * @param Exec 
 */
static void ProcessManagers(const TFunctionRef<void(UCoreManager* InManager)>& Exec)
{
	for (const auto& Manager : UManagerSubsystem::Get()->GetManagers())
	{
		Exec(Manager);
	}
}

/**
 * 
 * @param bAscending true则为按ProcedureOrder升序执行
 * @param Exec 
 */
static void ProcessManagersInOrder(bool bAscending, const TFunctionRef<void(UCoreManager* InCoreManager)>& Exec)
{
	TArray<FManagerOrder> ManagerOrders;
	for (auto& Manager : UManagerSubsystem::Get()->GetManagers())
	{
		if (!ManagerOrders.Contains(Manager->GetProcedureOrder()))
		{
			FManagerOrder NewManagerOrder = FManagerOrder(Manager->GetProcedureOrder());
			NewManagerOrder.Managers.Add(Manager);
			ManagerOrders.Add(NewManagerOrder);
		}
		else
		{
			FManagerOrder& FindManagerOrder = *ManagerOrders.FindByKey(Manager->GetProcedureOrder());
			FindManagerOrder.Managers.Add(Manager);
		}
	}

	ManagerOrders.Sort
	([bAscending](const FManagerOrder& A, const FManagerOrder& B)
		{
			return bAscending ? (A.Order < B.Order) : (A.Order > B.Order);
		}
	);

	for (auto& ManagerOrder : ManagerOrders)
	{
		for (const auto& Manager : ManagerOrder.Managers)
		{
			Exec(Manager);
		}
	}
}
