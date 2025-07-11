// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BackpackManager.h"

bool UBackpackManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UBackpackManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UBackpackManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}
