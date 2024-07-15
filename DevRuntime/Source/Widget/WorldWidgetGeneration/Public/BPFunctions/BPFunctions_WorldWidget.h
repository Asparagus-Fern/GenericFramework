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
	static void ActiveWorldWidgetPoint(AWorldWidgetPoint* InPoint);

	UFUNCTION(BlueprintCallable)
	static void ActiveWorldWidgetPointByTag(FGameplayTag InPointTag);

	UFUNCTION(BlueprintCallable)
	static void InactiveWorldWidgetPoint(AWorldWidgetPoint* InPoint);

	UFUNCTION(BlueprintCallable)
	static void InactiveWorldWidgetPointByTag(FGameplayTag InPointTag);

	UFUNCTION(BlueprintPure)
	static TArray<AWorldWidgetPoint*> GetWorldWidgetPoints();

	UFUNCTION(BlueprintPure)
	static TArray<AWorldWidgetPoint*> GetWorldWidgetPointsByTag(FGameplayTag InPointTag);
};
