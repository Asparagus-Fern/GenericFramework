// Copyright ChenTaiye 2025. All Rights Reserved.


#include "TerrainGenerationManager.h"

#include "Landscape.h"

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

void UTerrainGenerationManager::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	FCoreInternalManager::HandleOnWorldMatchStarting(InWorld);
	CreateNewLandScape();
}

void UTerrainGenerationManager::CreateNewLandScape()
{
}
