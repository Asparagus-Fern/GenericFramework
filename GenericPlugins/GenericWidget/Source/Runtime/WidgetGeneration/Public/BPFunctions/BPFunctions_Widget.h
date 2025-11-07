// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GenericWidgetSubsystem.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Widget.generated.h"

class UGenericWidget;

DECLARE_DYNAMIC_DELEGATE(FOnOpenGenericWidgetFinish);

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UBPFunctions_Widget : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static TArray<UGenericWidget*> GetActivedWidgets(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject", DeterminesOutputType = "InClass", Categories="UI"))
	static UGenericWidget* GetActivedWidget(const UObject* WorldContextObject, TSubclassOf<UGenericWidget> InClass, FGameplayTag InTag);
};
