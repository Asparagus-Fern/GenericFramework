// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreManager.h"

template <class ManagerType>
static ManagerType* GetManager(const UObject* WorldContextObject)
{
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		return World->GetSubsystem<ManagerType>();
	}
	return nullptr;
}

template <typename InterfaceClass>
static TArray<InterfaceClass*> GetManagersWithInterface(const UObject* WorldContextObject)
{
	TArray<InterfaceClass*> Managers;
	
	if (const UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject))
	{
		for (const auto& Manager : World->GetSubsystemArray<UCoreManager>())
		{
			if (Manager->GetClass()->ImplementsInterface(InterfaceClass::UClassType::StaticClass()))
			{
				Managers.Add(Cast<InterfaceClass>(Manager));
			}
		}
	}

	return Managers;
}
