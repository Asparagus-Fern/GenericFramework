// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

template <class ManagerType>
static ManagerType* GetManager()
{
	if (ManagerType::StaticClass()->IsChildOf(UCoreManager::StaticClass()))
	{
		if (const UWorld* World = ManagerType::GetStaticWorld())
		{
			return World->GetSubsystem<ManagerType>();
		}
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
