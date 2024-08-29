// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "GameFramework/Actor.h"
#include "WorldWidgetPoint.generated.h"

class UUserWidgetBase;
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Point);

UCLASS(HideCategories=(Object,Actor,Collision,Physics,Networking,Input,LevelInstance,Cooking,HLOD,Replication))
class WORLDWIDGETGENERATION_API AWorldWidgetPoint : public AActor
{
	GENERATED_BODY()

public:
	AWorldWidgetPoint(const FObjectInitializer& ObjectInitializer);
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

#if WITH_EDITORONLY_DATA

public:
	/* 预览 */
	UPROPERTY(EditAnywhere, Category="World Widget Point (Editor)")
	bool bPreview = true;

#endif

	/* AWorldWidgetPoint */
public:
	/* 当为false时自动激活显示，为true则手动控制显示 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsManual = false;

	/* 可通过标签获取到所有该标签点位 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Point"))
	FGameplayTag PointTag;

	/* 点位UI */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UUserWidgetBase* WorldWidget = nullptr;

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FWorldWidgetPointDelegate, AWorldWidgetPoint*);
	static FWorldWidgetPointDelegate OnWorldWidgetPointConstruct;
	static FWorldWidgetPointDelegate OnWorldWidgetPointRegister;
	static FWorldWidgetPointDelegate OnWorldWidgetPointUnRegister;
};
