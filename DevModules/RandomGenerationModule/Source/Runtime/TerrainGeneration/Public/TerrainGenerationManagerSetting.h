// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/ManagerSetting.h"
#include "TerrainGenerationManagerSetting.generated.h"

/**
 * 
 */
UCLASS()
class TERRAINGENERATION_API UTerrainGenerationManagerSetting : public UManagerSetting
{
	GENERATED_BODY()

public:
	static ThisClass* Get() { return GetMutableDefault<ThisClass>(); }

public:
};
