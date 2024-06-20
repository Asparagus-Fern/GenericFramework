// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "WorldWidgetPoint.generated.h"

class UWorldWidget;

UCLASS(HideCategories=(Object,Actor,Collision,Physics,Networking,Input,LevelInstance,Cooking,HLOD,Replication))
class WORLDWIDGETGENERATION_API AWorldWidgetPoint : public AActor
{
	GENERATED_BODY()

public:
	AWorldWidgetPoint(const FObjectInitializer& ObjectInitializer);
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/* Preview */
#if WITH_EDITORONLY_DATA

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="World Widget Point (Editor)")
	bool bPreview = true;

#endif

	/* AWorldWidgetPoint */
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Point"))
	FGameplayTag PointTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UWorldWidget* WorldWidget = nullptr;
};
