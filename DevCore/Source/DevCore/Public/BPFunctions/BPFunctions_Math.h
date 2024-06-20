// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Math.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_Math : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* Vector */
public:
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Middle (Vector)"), Category = "Math|Vector")
	static FVector Vector_Middle(FVector V1, FVector V2);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Rotate Middle (Vector)(Degrees)"), Category = "Math|Vector")
	static FVector Vector_Middle_Degrees(FVector V1, FVector V2, float Degrees);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Rotate Middle (Vector)(Radians)"), Category = "Math|Vector")
	static FVector Vector_Middle_Radians(FVector V1, FVector V2, float Radians);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Rotate Middle With Alpha (Vector)(Degrees)"), Category = "Math|Vector")
	static FVector Vector_Middle_Alpha_Degrees(FVector V1, FVector V2, float Alpha, float Degrees);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Rotate Middle With Alpha (Vector)(Radians)"), Category = "Math|Vector")
	static FVector Vector_Middle_Alpha_Radians(FVector V1, FVector V2, float Alpha, float Radians);

	/* Rotation*/
public:
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Get Safe Rotator", CompactNodeTitle = "Safe"), Category = "Math|Rotator")
	static FRotator Rotator_Safe(FRotator R);
};
