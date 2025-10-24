// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_GameHUD.generated.h"

class UGenericGameHUD;
/**
 * 
 */
UCLASS()
class WIDGETGENERATION_API UBPFunctions_GameHUD : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="GameHUD")
	static void CreateGameHUDListBySoftClass(const TArray<TSoftClassPtr<UGenericGameHUD>>& InGameHUDClasses);

	UFUNCTION(BlueprintCallable, Category="GameHUD")
	static void CreateGameHUDListByClass(TArray<TSubclassOf<UGenericGameHUD>> InGameHUDClasses);

	UFUNCTION(BlueprintCallable, Category="GameHUD")
	static void CreateGameHUDList(TArray<UGenericGameHUD*> InGameHUDs);

	UFUNCTION(BlueprintCallable, Category="GameHUD")
	static void CreateGameHUD(UGenericGameHUD* InGameHUD);

	UFUNCTION(BlueprintCallable, Category="GameHUD")
	static void RemoveGameHUDList(TArray<UGenericGameHUD*> InGameHUDs);

	UFUNCTION(BlueprintCallable, Category="GameHUD")
	static void RemoveGameHUD(UGenericGameHUD* InGameHUD);

	UFUNCTION(BlueprintCallable, Category="GameHUD")
	static void ClearAllGameHUD();
};
