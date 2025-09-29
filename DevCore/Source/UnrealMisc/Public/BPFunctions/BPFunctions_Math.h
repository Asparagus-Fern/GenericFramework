// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Math.generated.h"

/**
 * 
 */
UCLASS()
class UNREALMISC_API UBPFunctions_Math : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* Vector */
public:
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Middle (Vector)(Degrees)", AdvancedDisplay = "2"), Category = "Math|Vector")
	static FVector Vector_MiddleDegrees(const FVector& V1, const FVector& V2, float Alpha = .5f, float Degrees = 0.f);

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Middle (Vector)(Radians)", AdvancedDisplay = "2"), Category = "Math|Vector")
	static FVector Vector_MiddleRadians(const FVector& V1, const FVector& V2, float Alpha = .5f, float Radians = 0.f);

	/*
	 * Map Clamp InValue.X From Range(InRangeA.X , InRangeB.X) To Range(OutRangeA.X , OutRangeB.X)
	 * Map Clamp InValue.Y From Range(InRangeA.Y , InRangeB.Y) To Range(OutRangeA.Y , OutRangeB.Y)
	 * Map Clamp InValue.Z From Range(InRangeA.Z , InRangeB.Z) To Range(OutRangeA.Z , OutRangeB.Z)
	 */
	// UFUNCTION(BlueprintPure, meta=(DisplayName = "Map Range Clamped (Vector)"), Category = "Math|Vector")
	// static FVector Vector_MapRangeClamped(const FVector& InValue, const FVector& InRangeA, const FVector& InRangeB, const FVector& OutRangeA, const FVector& OutRangeB);

	/*
	 * Map Unclamped InValue.X From Range(InRangeA.X , InRangeB.X) To Range(OutRangeA.X , OutRangeB.X)
	 * Map Unclamped InValue.Y From Range(InRangeA.Y , InRangeB.Y) To Range(OutRangeA.Y , OutRangeB.Y)
	 * Map Unclamped InValue.Z From Range(InRangeA.Z , InRangeB.Z) To Range(OutRangeA.Z , OutRangeB.Z)
	 */
	// UFUNCTION(BlueprintPure, meta=(DisplayName = "Map Range Unclamped (Vector)"), Category = "Math|Vector")
	// static FVector Vector_MapRangeUnclamped(const FVector& InValue, const FVector& InRangeA, const FVector& InRangeB, const FVector& OutRangeA, const FVector& OutRangeB);

	/* Rotation*/
public:
	UFUNCTION(BlueprintPure, meta=(DisplayName = "Get Safe Rotator", CompactNodeTitle = "Safe"), Category = "Math|Rotator")
	static FRotator Rotator_Safe(FRotator R);

	/*
	 * Map Clamp InValue.Pitch From Range(InRangeA.Pitch , InRangeB.Pitch) To Range(OutRangeA.Pitch , OutRangeB.Pitch)
	 * Map Clamp InValue.Yaw From Range(InRangeA.Yaw , InRangeB.Yaw) To Range(OutRangeA.Yaw , OutRangeB.Yaw)
	 * Map Clamp InValue.Roll From Range(InRangeA.Roll , InRangeB.Roll) To Range(OutRangeA.Roll , OutRangeB.Roll)
	 */
	// UFUNCTION(BlueprintPure, meta=(DisplayName = "Map Range Clamped (Rotator)"), Category = "Math|Rotator")
	// static FRotator Rotator_MapRangeClamped(const FRotator& InValue, const FRotator& InRangeA, const FRotator& InRangeB, const FRotator& OutRangeA, const FRotator& OutRangeB);

	/*
	 * Map Unclamped InValue.Pitch From Range(InRangeA.Pitch , InRangeB.Pitch) To Range(OutRangeA.Pitch , OutRangeB.Pitch)
	 * Map Unclamped InValue.Yaw From Range(InRangeA.Yaw , InRangeB.Yaw) To Range(OutRangeA.Yaw , OutRangeB.Yaw)
	 * Map Unclamped InValue.Roll From Range(InRangeA.Roll , InRangeB.Roll) To Range(OutRangeA.Roll , OutRangeB.Roll)
	 */
	// UFUNCTION(BlueprintPure, meta=(DisplayName = "Map Range Unclamped (Rotator)"), Category = "Math|Rotator")
	// static FRotator Rotator_MapRangeUnclamped(const FRotator& InValue, const FRotator& InRangeA, const FRotator& InRangeB, const FRotator& OutRangeA, const FRotator& OutRangeB);

	/* Vector2D */
public:
	/*
	 * Map Clamp InValue.X From Range(InRangeA.X , InRangeB.X) To Range(OutRangeA.X , OutRangeB.X)
	 * Map Clamp InValue.Y From Range(InRangeA.Y , InRangeB.Y) To Range(OutRangeA.Y , OutRangeB.Y)
	 */
	// UFUNCTION(BlueprintPure, meta=(DisplayName = "Map Range Clamped (Vector2D)"), Category = "Math|Vector2D")
	// static FVector2D Vector2D_MapRangeClamped(const FVector2D& InValue, const FVector2D& InRangeA, const FVector2D& InRangeB, const FVector2D& OutRangeA, const FVector2D& OutRangeB);

	/*
	 * Map Unclamped InValue.X From Range(InRangeA.X , InRangeB.X) To Range(OutRangeA.X , OutRangeB.X)
	 * Map Unclamped InValue.Y From Range(InRangeA.Y , InRangeB.Y) To Range(OutRangeA.Y , OutRangeB.Y)
	 */
	// UFUNCTION(BlueprintPure, meta=(DisplayName = "Map Range Unclamped (Vector2D)"), Category = "Math|Vector2D")
	// static FVector2D Vector2D_MapRangeUnclamped(const FVector2D& InValue, const FVector2D& InRangeA, const FVector2D& InRangeB, const FVector2D& OutRangeA, const FVector2D& OutRangeB);
};
