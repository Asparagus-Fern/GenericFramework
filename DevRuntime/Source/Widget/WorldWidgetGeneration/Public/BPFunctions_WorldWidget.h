// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_WorldWidget.generated.h"

class AWorldWidgetPoint;
/**
 * 
 */
UCLASS()
class WORLDWIDGETGENERATION_API UBPFunctions_WorldWidget : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void RegisterWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint);

	UFUNCTION(BlueprintCallable)
	static void UnRegisterWorldWidgetPoint(AWorldWidgetPoint* WorldWidgetPoint);

	UFUNCTION(BlueprintPure)
	static TArray<AWorldWidgetPoint*> GetWorldWidgetPoints();

	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="Point"))
	static AWorldWidgetPoint* FindWorldWidgetPoint(FGameplayTag PointTag);

	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="Point"))
	static TArray<AWorldWidgetPoint*> FindWorldWidgetPoints(FGameplayTag PointTag);
};
