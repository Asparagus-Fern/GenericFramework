// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WorldWidgetComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_WorldWidget.generated.h"

class AWorldWidgetPoint;
class UWorldWidgetComponent;
class UInteractableWidgetEntityGroup;

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
	
public:
	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="UI.WorldWidget"))
	static UInteractableWidgetEntityGroup* GetWorldWidgetGroup(FGameplayTag InGroupTag);
};
