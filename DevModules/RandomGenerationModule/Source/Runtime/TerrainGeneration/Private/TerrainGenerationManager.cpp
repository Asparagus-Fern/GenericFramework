// Fill out your copyright notice in the Description page of Project Settings.


#include "TerrainGenerationManager.h"

bool UTerrainGenerationManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UTerrainGenerationManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UTerrainGenerationManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool UTerrainGenerationManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}
