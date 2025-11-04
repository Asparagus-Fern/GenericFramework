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
	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category="GameHUD")
	static void CreateGameHUDList(const UObject* WorldContextObject, TArray<UGenericGameHUD*> InGameHUDs);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category="GameHUD")
	static void CreateGameHUD(const UObject* WorldContextObject, UGenericGameHUD* InGameHUD);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category="GameHUD")
	static void RemoveGameHUDList(const UObject* WorldContextObject, TArray<UGenericGameHUD*> InGameHUDs);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category="GameHUD")
	static void RemoveGameHUD(const UObject* WorldContextObject, UGenericGameHUD* InGameHUD);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"), Category="GameHUD")
	static void ClearAllGameHUD(const UObject* WorldContextObject);
};
