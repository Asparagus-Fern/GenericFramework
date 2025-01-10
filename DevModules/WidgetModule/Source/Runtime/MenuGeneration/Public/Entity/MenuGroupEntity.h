// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuEntity.h"
#include "MenuGroupEntity.generated.h"

/**
 * 
 */
UCLASS()
class MENUGENERATION_API UMenuGroupEntity : public UMenuEntity
{
	GENERATED_BODY()

public:
	UMenuGroupEntity(const FObjectInitializer& ObjectInitializer);
	virtual void Initialize() override;
	virtual void DeInitialize() override;

public:
	UPROPERTY()
	bool bUseContainerClass = false;

	/* 菜单容器类 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditConditionHides, EditCondition = "bUseContainerClass"))
	TSubclassOf<UMenuContainer> ContainerClass = nullptr;

	/* 菜单容器 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, meta=(EditConditionHides, EditCondition = "!bUseContainerClass"))
	UMenuContainer* Container = nullptr;
};
