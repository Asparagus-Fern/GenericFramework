// Fill out your copyright notice in the Description page of Project Settings.


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
