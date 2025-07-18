// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Manager/GlobalTimerManager.h"

bool UGlobalTimerManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGlobalTimerManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UGlobalTimerManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}
