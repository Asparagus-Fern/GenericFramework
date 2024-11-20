// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_WorldWidget.generated.h"

class AWorldWidgetPoint;
class UWorldWidgetComponent;
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

	UFUNCTION(BlueprintCallable)
	static void RegisterWorldWidgetComponent(UWorldWidgetComponent* WorldWidgetComponent);

	UFUNCTION(BlueprintCallable)
	static void UnRegisterWorldWidgetComponent(UWorldWidgetComponent* WorldWidgetComponent);

	UFUNCTION(BlueprintPure)
	static TArray<UWorldWidgetComponent*> GetWorldWidgetComponents();

	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="UI.WorldWidget"))
	static UWorldWidgetComponent* FindWorldWidgetComponent(FGameplayTag WorldWidgetTag);

	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="UI.WorldWidget"))
	static TArray<UWorldWidgetComponent*> FindWorldWidgetComponents(FGameplayTag WorldWidgetTag);
};
