// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PickableItemInterface.h"
#include "PickableItemComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(DevPlugin), meta=(BlueprintSpawnableComponent))
class BACKPACKSYSTEM_API UPickableItemComponent : public UActorComponent, public IPickableItemInterface
{
	GENERATED_BODY()

public:
	UPickableItemComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
};
