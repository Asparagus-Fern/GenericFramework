// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildingsInteractionType.h"
#include "Actor/CommonActor.h"
#include "FloorActor.generated.h"

class UFloorBodyComponent;
class UFloorPreset;

/**
 * 
 */
UCLASS()
class BUILDINGSINTERACTIONSYSTEM_API AFloorActor : public ACommonActor
{
	GENERATED_BODY()

public:
	AFloorActor();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UFloorBodyComponent* FloorBodyComponent = nullptr;
};
