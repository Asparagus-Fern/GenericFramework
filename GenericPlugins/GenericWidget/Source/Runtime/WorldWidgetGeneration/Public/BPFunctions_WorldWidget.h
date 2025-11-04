// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WorldWidgetComponent.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_WorldWidget.generated.h"

class AWorldWidgetPoint;
class UWorldWidgetComponent;
class UGenericButtonGroup;

/**
 * 
 */
UCLASS()
class WORLDWIDGETGENERATION_API UBPFunctions_WorldWidget : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static TArray<UWorldWidgetComponent*> GetWorldWidgetComponents(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static TArray<UWorldWidgetComponent*> GetWorldWidgetComponents2D(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static TArray<UWorldWidgetComponent*> GetWorldWidgetComponents3D(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="UI.WorldWidget"))
	static UWorldWidgetComponent* FindWorldWidgetComponent(const UObject* WorldContextObject, FGameplayTag WorldWidgetTag);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="UI.WorldWidget"))
	static TArray<UWorldWidgetComponent*> FindWorldWidgetComponents(const UObject* WorldContextObject, FGameplayTag WorldWidgetTag);

public:
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="UI.WorldWidget"))
	static UGenericButtonGroup* GetWorldWidgetGroup(const UObject* WorldContextObject, FGameplayTag InGroupTag);
};
