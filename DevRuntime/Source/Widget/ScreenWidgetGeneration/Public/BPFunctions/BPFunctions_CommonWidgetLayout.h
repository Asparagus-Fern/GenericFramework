// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_CommonWidgetLayout.generated.h"

class UButtonSlot;
class UWidget;
class UStackBoxSlot;

/**
 * 
 */
UCLASS()
class SCREENWIDGETGENERATION_API UBPFunctions_CommonWidgetLayout : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="Slot")
	static UStackBoxSlot* SlotAsStackBoxSlot(UWidget* Widget);

	UFUNCTION(BlueprintPure, Category="Slot")
	static UButtonSlot* SlotAsButtonSlot(UWidget* Widget);
};
