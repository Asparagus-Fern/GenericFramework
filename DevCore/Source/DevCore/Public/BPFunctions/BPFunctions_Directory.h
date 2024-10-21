// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Directory.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_Directory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* Plugin */
public:
	UFUNCTION(BlueprintPure)
	static bool GetPluginBaseDir(const FString& InPluginName, FString& Directory);

	UFUNCTION(BlueprintPure)
	static bool GetPluginBinariesDir(const FString& InPluginName, FString& Directory);

	UFUNCTION(BlueprintPure)
	static bool GetPluginContentDir(const FString& InPluginName, FString& Directory);

	UFUNCTION(BlueprintPure)
	static bool GetPluginIntermediateDir(const FString& InPluginName, FString& Directory);

	UFUNCTION(BlueprintPure)
	static bool GetPluginResourcesDir(const FString& InPluginName, FString& Directory);

	UFUNCTION(BlueprintPure)
	static bool GetPluginSourceDir(const FString& InPluginName, FString& Directory);

	UFUNCTION(BlueprintPure)
	static bool GetPluginExtraDir(const FString& InPluginName, FString& Directory);
};
