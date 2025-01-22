// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_GameHUD.generated.h"

class UGameplayTagSlot;

/**
 * 
 */
UCLASS()
class GAMEHUDMODULE_API UBPFunctions_GameHUD : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* UGameplayTagSlot */
public:
	UFUNCTION(BlueprintCallable)
	static void RegisterSlot(UGameplayTagSlot* InSlot);

	UFUNCTION(BlueprintCallable)
	static void UnRegisterSlot(UGameplayTagSlot* InSlot);

	UFUNCTION(BlueprintPure)
	static bool GetSlots(TArray<UGameplayTagSlot*>& Slots);

	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="UI.HUD"))
	static UGameplayTagSlot* GetSlot(FGameplayTag InSlotTag);
};
