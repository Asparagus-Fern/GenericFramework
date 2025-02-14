// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/CoreInternalManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "TerrainGenerationManager.generated.h"

class ALandscape;

/**
 * 
 */
UCLASS()
class TERRAINGENERATION_API UTerrainGenerationManager : public UWorldSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;

public:
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override;
	void CreateNewTerrain();

private:
	TObjectPtr<ALandscape> Terrain;
};
