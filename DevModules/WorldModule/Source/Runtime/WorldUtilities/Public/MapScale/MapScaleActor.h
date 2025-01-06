// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MapScaleActor.generated.h"

UCLASS(NotBlueprintable,HideCategories=(Object,Collision,Physics,Networking,Input,LevelInstance,Cooking,LOD,HLOD,Replication))
class WORLDUTILITIES_API AMapScaleActor : public AActor
{
	GENERATED_BODY()

public:
	AMapScaleActor();
	virtual void BeginPlay() override;
	// virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent = nullptr;
};
