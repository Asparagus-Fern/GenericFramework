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
	UFUNCTION(BlueprintCallable, meta = (DeterminesOutputType = "InWidgetClass"), DisplayName="OpenGenericWidgetByClass")
	static UGenericWidget* BP_OpenGenericWidgetByClass(TSubclassOf<UGenericWidget> InWidgetClass);

	UFUNCTION(BlueprintCallable, DisplayName="OpenGenericWidget")
	static bool BP_OpenGenericWidget(UGenericWidget* InWidget);

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="UI.HUD"), DisplayName="CloseGenericWidgetByTag")
	static bool BP_CloseGenericWidgetByTag(FGameplayTag InSlotTag, bool MarkAsGarbage = true);

	UFUNCTION(BlueprintCallable, DisplayName="CloseGenericWidget")
	static bool BP_CloseGenericWidget(UGenericWidget* InWidget, bool MarkAsGarbage = true);

	UFUNCTION(BlueprintPure)
	static TArray<UGenericWidget*> GetActivedWidgets();
};
