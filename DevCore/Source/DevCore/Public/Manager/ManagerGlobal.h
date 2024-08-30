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
