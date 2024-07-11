// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Procedure.generated.h"

class UGameplayProcedure;
/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_Procedure : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void SwitchProcedure(FGameplayTag InProcedureTag, bool bForce = false);

	UFUNCTION(BlueprintPure)
	static UGameplayProcedure* GetGameplayProcedure(FGameplayTag InProcedureTag);

	UFUNCTION(BlueprintPure)
	static FGameplayTag GetLastProcedureTag();

	UFUNCTION(BlueprintPure)
	static FGameplayTag GetCurrentProcedureTag();

	UFUNCTION(BlueprintPure)
	static TMap<FGameplayTag, UGameplayProcedure*>& GetGameplayProcedureMapping();
};
