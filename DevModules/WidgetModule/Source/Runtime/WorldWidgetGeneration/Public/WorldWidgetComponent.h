// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "Components/SceneComponent.h"
#include "WorldWidgetComponent.generated.h"

class UUserWidgetBase;

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_WorldWidget);

/**
 * 创建出一个基于屏幕的3DUI
 */
UCLASS(ClassGroup=(Developer), meta=(BlueprintSpawnableComponent))
class WORLDWIDGETGENERATION_API UWorldWidgetComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UWorldWidgetComponent();
	virtual void OnRegister() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	DECLARE_EVENT_OneParam(UWorldWidgetComponent, FWorldWidgetComponentDelegate, UWorldWidgetComponent*);

	static FWorldWidgetComponentDelegate OnWorldWidgetComponentRegister;
	static FWorldWidgetComponentDelegate OnWorldWidgetPointBeginPlay;
	static FWorldWidgetComponentDelegate OnWorldWidgetPointEndPlay;

public:
	/* 是否自动注册 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsAutoRegister = true;

	/* 当为false时自动激活显示，为true则手动控制显示 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsManualActive = false;

	/* 可通过标签获取到所有该标签组件 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.WorldWidget"))
	FGameplayTag WorldWidgetTag = FGameplayTag::EmptyTag;

	/* UI */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	UUserWidgetBase* WorldWidget = nullptr;
};
