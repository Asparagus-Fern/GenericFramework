// Fill out your copyright notice in the Description page of Project Settings.


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
	CreateNewTerrain();
}

void UTerrainGenerationManager::CreateNewTerrain()
{
	UWorld* World = GetWorld();
	const bool bCreateTerrain = World != nullptr && World->GetCurrentLevel()->bIsVisible;
	if (!bCreateTerrain)
	{
		DLOG(DLogTerrain, Warning, TEXT("Fail To Create"))
		return;
	}

	Terrain = World->SpawnActor<ALandscape>();
	Terrain->StaticLightingLOD = 0;
}
