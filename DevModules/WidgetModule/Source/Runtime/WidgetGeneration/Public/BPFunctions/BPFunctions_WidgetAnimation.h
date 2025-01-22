// Fill out your copyright notice in the Description page of Project Settings.

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
