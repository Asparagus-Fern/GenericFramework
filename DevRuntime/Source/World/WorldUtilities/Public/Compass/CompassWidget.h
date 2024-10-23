// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UserWidget/Base/UserWidgetBase.h"
#include "CompassWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class WORLDUTILITIES_API UCompassWidget : public UUserWidgetBase
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure)
	float GetPlayerPointToNorthAngle() const;

	UFUNCTION(BlueprintPure)
	float GetPlayerPitchAngle() const;

protected:
	UFUNCTION(BlueprintNativeEvent)
	float GetUIPointToNorthAngle();
};
