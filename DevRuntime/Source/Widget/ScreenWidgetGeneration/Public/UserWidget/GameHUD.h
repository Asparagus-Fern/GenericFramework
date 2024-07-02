// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/UserWidgetBase.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class SCREENWIDGETGENERATION_API UGameHUD : public UUserWidgetBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Getter, BlueprintGetter="GetViewportZOrder")
	int32 ViewportZOrder = 0;

public:
	UFUNCTION(BlueprintPure)
	int32 GetViewportZOrder() const;
};
