// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GenericWidgetManager.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Widget.generated.h"

class UGenericWidget;

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UBPFunctions_Widget : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InWidgetClass"))
	static UGenericWidget* OpenUserWidgetByClass(TSubclassOf<UGenericWidget> InWidgetClass);

	UFUNCTION(BlueprintCallable)
	static bool OpenUserWidget(UGenericWidget* InWidget);

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="UI.HUD"))
	static bool CloseUserWidgetByTag(FGameplayTag InSlotTag, bool MarkAsGarbage = true);

	UFUNCTION(BlueprintCallable)
	static bool CloseUserWidget(UGenericWidget* InWidget, bool MarkAsGarbage = true);

	UFUNCTION(BlueprintPure)
	static TArray<UGenericWidget*> GetActivedWidgets();
};
