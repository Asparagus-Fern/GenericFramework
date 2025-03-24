// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MapScaleActor.generated.h"

UCLASS(NotBlueprintable, HideCategories=(Object,Collision,Physics,Networking,Input,LevelInstance,Cooking,LOD,HLOD,Replication), MinimalAPI)
class AMapScaleActor : public AActor
{
	GENERATED_BODY()

public:
	AMapScaleActor();
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent = nullptr;
};
