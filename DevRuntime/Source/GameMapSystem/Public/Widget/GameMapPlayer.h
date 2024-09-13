// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlateType.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "GameMapPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GAMEMAPSYSTEM_API UGameMapPlayer : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	FImageBrush PlayerImageBrush;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn = true))
	FImageBrush PlayerForwardImageBrush;
};
