// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Base/UserWidgetBase.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class UMGUTILITIES_API UGameHUD : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="UI.HUD"))
	FGameplayTag HUDTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ViewportZOrder = 0;
};
