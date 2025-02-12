// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WorldWidgetComponent.h"
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
	UFUNCTION(BlueprintPure)
	static TArray<UWorldWidgetComponent*> GetWorldWidgetComponents();

	UFUNCTION(BlueprintPure)
	static TArray<UWorldWidgetComponent*> GetWorldWidgetComponents2D();

	UFUNCTION(BlueprintPure)
	static TArray<UWorldWidgetComponent*> GetWorldWidgetComponents3D();

	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="UI.WorldWidget"))
	static UWorldWidgetComponent* FindWorldWidgetComponent(FGameplayTag WorldWidgetTag);

	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="UI.WorldWidget"))
	static TArray<UWorldWidgetComponent*> FindWorldWidgetComponents(FGameplayTag WorldWidgetTag);

	UFUNCTION(BlueprintCallable, DisplayName="SetWorldWidgetComponentActiveState(Actor)")
	static void SetWorldWidgetComponentActiveStateWithActor(AActor* InActor, bool IsActive);

	UFUNCTION(BlueprintCallable, DisplayName="SetWorldWidgetComponentActiveState(Component)")
	static void SetWorldWidgetComponentActiveStateWithComponent(UWorldWidgetComponent* InWorldWidgetComponent, bool IsActive);

	UFUNCTION(BlueprintCallable)
	static void SetWorldWidgetPaintMethod(UWorldWidgetComponent* InWorldWidgetComponent, EWorldWidgetPaintMethod WorldWidgetPaintMethod);

	UFUNCTION(BlueprintCallable)
	static void SetWorldWidgetLookAtSetting(UWorldWidgetComponent* InWorldWidgetComponent, FWorldWidgetLookAtSetting WorldWidgetLookAtSetting);
};
