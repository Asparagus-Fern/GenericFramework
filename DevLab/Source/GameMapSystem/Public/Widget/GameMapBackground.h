// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateType.h"
#include "Base/UserWidgetBase.h"
#include "GameMapBackground.generated.h"

/**
 * 
 */
UCLASS()
class GAMEMAPSYSTEM_API UGameMapBackground : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	FImageBrush BackgroundImageBrush;
};
