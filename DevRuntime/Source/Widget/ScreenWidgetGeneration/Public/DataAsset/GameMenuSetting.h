// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScreenWidgetType.h"
#include "Engine/DataAsset.h"
#include "GameMenuSetting.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class SCREENWIDGETGENERATION_API UGameMenuSetting : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UDataTable* MenuTagTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (TitleProperty = "ContainerTag"))
	TArray<FMenuContainerInfo> MenuContainerInfos;

public:
#if WITH_EDITOR
	UFUNCTION(CallInEditor)
	void GenerateMenu();
#endif

public:
	FMenuContainerInfo* GetRootContainerInfo();
	FMenuContainerInfo* GetContainerInfo(FGameplayTag InContainerTag);
};
