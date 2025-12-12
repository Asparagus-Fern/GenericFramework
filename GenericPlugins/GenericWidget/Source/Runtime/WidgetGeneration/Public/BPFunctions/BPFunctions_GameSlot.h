// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_GameSlot.generated.h"

class UGenericWidget;
class UGameplayTagSlot;

/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UBPFunctions_GameSlot : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* UGameplayTagSlot */
public:
	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category="GameSlot")
	static void RegisterSlot(const UObject* WorldContextObject, UGameplayTagSlot* InSlot);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category="GameSlot")
	static void UnRegisterSlot(const UObject* WorldContextObject, UGameplayTagSlot* InSlot);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject", Categories="UI.HUD"), Category="GameSlot")
	static UGameplayTagSlot* GetSlot(const UObject* WorldContextObject, FGameplayTag InTag);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject", DeterminesOutputType = "InClass", Categories="UI.HUD"), Category="GameSlot")
	static UGenericWidget* GetSlotWidget(const UObject* WorldContextObject, TSubclassOf<UGenericWidget> InClass, FGameplayTag InTag);
};
