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
	virtual void Destroyed() override;

	/* Preview */
#if WITH_EDITORONLY_DATA

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="World Widget Point (Editor)")
	bool bPreview = true;

#endif

	/* AWorldWidgetPoint */
public:
	/* 被添加进WorldWidgetManager时自动激活，显示到屏幕上，为false则为手动控制 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsAutoActived = true;

	/* 可通过标签获取到所有该标签点位 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Point"))
	FGameplayTag PointTag;

	/* 该点位顺序 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Order = 0;

	/* 点位UI */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UWorldWidget* WorldWidget = nullptr;
};
