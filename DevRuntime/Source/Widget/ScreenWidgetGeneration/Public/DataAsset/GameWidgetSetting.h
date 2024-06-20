// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameWidgetSetting.generated.h"

class UUserWidgetBase;
class UGameMenuSetting;

/**
 * 
 */
UCLASS(BlueprintType)
class SCREENWIDGETGENERATION_API UGameWidgetSetting : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UGameMenuSetting* GameMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<UUserWidgetBase*> OpenUserWidgetsOnLoading;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<UUserWidgetBase*> DefaultOpenUserWidgets;

public:
};
