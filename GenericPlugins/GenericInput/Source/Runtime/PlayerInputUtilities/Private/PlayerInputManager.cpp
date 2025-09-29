// Copyright ChenTaiye 2025. All Rights Reserved.


#include "PlayerInputManager.h"

bool UPlayerInputManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UPlayerInputManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UPlayerInputManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}
