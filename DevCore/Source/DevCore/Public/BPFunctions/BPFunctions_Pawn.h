// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Pawn.generated.h"

class IPawnInputMovementInterface;

/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_Pawn : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="Pawn"))
	// static void PossessPawn(int32 PlayerIndex, FGameplayTag InPawnTag);
	//
	// UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="Pawn"))
	// static APawn* GetPawn(FGameplayTag InPawnTag);
};
