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

static void ProcessManagers(const TFunctionRef<void(UCoreManager* InManager)>& Exec)
{
	for (const auto& Manager : UManagerSubsystem::Get()->GetManagers())
	{
		Exec(Manager);
	}
}
