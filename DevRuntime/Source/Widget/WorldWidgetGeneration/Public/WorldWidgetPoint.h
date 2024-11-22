// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "GameFramework/Actor.h"
#include "WorldWidgetPoint.generated.h"

class UWorldWidgetComponent;
class UUserWidgetBase;


UCLASS(HideCategories=(Object,Collision,Physics,Networking,Input,LevelInstance,Cooking,HLOD,Replication))
class WORLDWIDGETGENERATION_API AWorldWidgetPoint : public AActor
{
	GENERATED_BODY()

public:
	AWorldWidgetPoint(const FObjectInitializer& ObjectInitializer);

public:
#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere)
	FString MiddleClick = "Mouse Button Middle Click UMG To Select The Actor";
#endif

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UWorldWidgetComponent* WorldWidgetComponent = nullptr;
};
