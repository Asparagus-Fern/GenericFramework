// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_GenericButtonWidget.generated.h"

class UGenericButtonCollection;

/**
 * 
 */
UCLASS()
class WIDGETGROUPGENERATION_API UBPFunctions_GenericButtonWidget : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InCollectionClass"))
	static UGenericButtonCollection* RegisterButtonCollectionByClass(const UObject* WorldContextObject, APlayerController* Player, TSubclassOf<UGenericButtonCollection> InCollectionClass, bool InActived = true);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static bool UnRegisterButtonCollection(const UObject* WorldContextObject, UGenericButtonCollection* InCollection);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static bool IsButtonCollectionRegistered(const UObject* WorldContextObject, UGenericButtonCollection* InCollection, bool& IsRegistered);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static bool GetAllButtonCollection(const UObject* WorldContextObject, TArray<UGenericButtonCollection*>& Collections);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject", DeterminesOutputType = "InCollectionClass", GameplayTagFilter="UI.Button"))
	static UGenericButtonCollection* GetButtonCollectionByTag(const UObject* WorldContextObject, TSubclassOf<UGenericButtonCollection> InCollectionClass, FGameplayTag InRootButtonTag);
};
