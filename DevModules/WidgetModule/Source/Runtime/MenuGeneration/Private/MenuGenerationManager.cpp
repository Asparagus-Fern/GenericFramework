// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuGenerationManager.h"

bool UMenuGenerationManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UMenuGenerationManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UMenuGenerationManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool UMenuGenerationManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}
