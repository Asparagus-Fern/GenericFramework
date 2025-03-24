// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_WidgetAnimation.generated.h"

class UUserWidgetBase;

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UBPFunctions_WidgetAnimation : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static bool PlayWidgetAnimation(UUserWidgetBase* InWidget, bool InIsActive);
};
