// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "GameFramework/Actor.h"
#include "WorldWidgetPoint.generated.h"

class UWorldWidgetComponent;
class UUserWidgetBase;


UCLASS(HideCategories=(Object,Actor,Collision,Physics,Networking,Input,LevelInstance,Cooking,HLOD,Replication))
class WORLDWIDGETGENERATION_API AWorldWidgetPoint : public AActor
{
	GENERATED_BODY()

public:
	AWorldWidgetPoint(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWorldWidgetComponent* WorldWidgetComponent = nullptr;
};
