// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_GameSlot.generated.h"

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
	UFUNCTION(BlueprintCallable, Category="GameSlot")
	static void RegisterSlot(UGameplayTagSlot* InSlot);

	UFUNCTION(BlueprintCallable, Category="GameSlot")
	static void UnRegisterSlot(UGameplayTagSlot* InSlot);
};
