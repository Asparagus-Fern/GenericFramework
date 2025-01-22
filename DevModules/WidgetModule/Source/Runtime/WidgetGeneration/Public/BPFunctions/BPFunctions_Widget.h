// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WidgetManager.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Widget.generated.h"

class UUserWidgetBase;

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UBPFunctions_Widget : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InWidgetClass"))
	static UUserWidgetBase* OpenUserWidgetByClass(TSubclassOf<UUserWidgetBase> InWidgetClass);

	UFUNCTION(BlueprintCallable)
	static bool OpenUserWidget(UUserWidgetBase* InWidget);

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="UI.HUD"))
	static bool CloseUserWidgetByTag(FGameplayTag InSlotTag, bool MarkAsGarbage = true);

	UFUNCTION(BlueprintCallable)
	static bool CloseUserWidget(UUserWidgetBase* InWidget, bool MarkAsGarbage = true);

	UFUNCTION(BlueprintPure)
	static TArray<UUserWidgetBase*> GetActivedWidgets();
};
