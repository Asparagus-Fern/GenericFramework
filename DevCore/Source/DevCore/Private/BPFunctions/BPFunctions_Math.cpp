// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Math.h"

FVector UBPFunctions_Math::Vector_MiddleDegrees(const FVector& V1, const FVector& V2, const float Alpha, const float Degrees)
{
	return (FRotator(0.f, FMath::Clamp(Degrees, -90.f, 90.f), 0.f).RotateVector((V2 - V1).GetSafeNormal(.0001f)))
		* ((FVector::Distance(V1, V2) * FMath::Clamp(Alpha, 0.f, 1.f)) / FMath::Cos(UE_DOUBLE_PI / (180.0) * Degrees))
		+ V1;
}

FVector UBPFunctions_Math::Vector_MiddleRadians(const FVector& V1, const FVector& V2, const float Alpha, const float Radians)
{
	return Vector_MiddleDegrees(V1, V2, Alpha, FMath::RadiansToDegrees(Radians));
}

FVector UBPFunctions_Math::Vector_MapRangeClamped(const FVector& InValue, const FVector& InRangeA, const FVector& InRangeB, const FVector& OutRangeA, const FVector& OutRangeB)
{
	return FVector
	(
		FMath::GetMappedRangeValueClamped(FVector2D(InRangeA.X, InRangeB.X), FVector2D(OutRangeA.X, OutRangeB.X), InValue.X),
		FMath::GetMappedRangeValueClamped(FVector2D(InRangeA.Y, InRangeB.Y), FVector2D(OutRangeA.Y, OutRangeB.Y), InValue.Y),
		FMath::GetMappedRangeValueClamped(FVector2D(InRangeA.Z, InRangeB.Z), FVector2D(OutRangeA.Z, OutRangeB.Z), InValue.Z)
	);
}

FVector UBPFunctions_Math::Vector_MapRangeUnclamped(const FVector& InValue, const FVector& InRangeA, const FVector& InRangeB, const FVector& OutRangeA, const FVector& OutRangeB)
{
	return FVector
	(
		FMath::GetMappedRangeValueUnclamped(FVector2D(InRangeA.X, InRangeB.X), FVector2D(OutRangeA.X, OutRangeB.X), InValue.X),
		FMath::GetMappedRangeValueUnclamped(FVector2D(InRangeA.Y, InRangeB.Y), FVector2D(OutRangeA.Y, OutRangeB.Y), InValue.Y),
		FMath::GetMappedRangeValueUnclamped(FVector2D(InRangeA.Z, InRangeB.Z), FVector2D(OutRangeA.Z, OutRangeB.Z), InValue.Z)
	);
}

FRotator UBPFunctions_Math::Rotator_Safe(FRotator R)
{
	return FRotator(R.Pitch, FRotator::ClampAxis(R.Yaw + R.Roll), 0.f);
}

FRotator UBPFunctions_Math::Rotator_MapRangeClamped(const FRotator& InValue, const FRotator& InRangeA, const FRotator& InRangeB, const FRotator& OutRangeA, const FRotator& OutRangeB)
{
	return FRotator
	(
		FMath::GetMappedRangeValueClamped(FVector2D(InRangeA.Pitch, InRangeB.Pitch), FVector2D(OutRangeA.Pitch, OutRangeB.Pitch), InValue.Pitch),
		FMath::GetMappedRangeValueClamped(FVector2D(InRangeA.Yaw, InRangeB.Yaw), FVector2D(OutRangeA.Yaw, OutRangeB.Yaw), InValue.Yaw),
		FMath::GetMappedRangeValueClamped(FVector2D(InRangeA.Roll, InRangeB.Roll), FVector2D(OutRangeA.Roll, OutRangeB.Roll), InValue.Roll)
	);
}

FRotator UBPFunctions_Math::Rotator_MapRangeUnclamped(const FRotator& InValue, const FRotator& InRangeA, const FRotator& InRangeB, const FRotator& OutRangeA, const FRotator& OutRangeB)
{
	return FRotator
	(
		FMath::GetMappedRangeValueUnclamped(FVector2D(InRangeA.Pitch, InRangeB.Pitch), FVector2D(OutRangeA.Pitch, OutRangeB.Pitch), InValue.Pitch),
		FMath::GetMappedRangeValueUnclamped(FVector2D(InRangeA.Yaw, InRangeB.Yaw), FVector2D(OutRangeA.Yaw, OutRangeB.Yaw), InValue.Yaw),
		FMath::GetMappedRangeValueUnclamped(FVector2D(InRangeA.Roll, InRangeB.Roll), FVector2D(OutRangeA.Roll, OutRangeB.Roll), InValue.Roll)
	);
}

FVector2D UBPFunctions_Math::Vector2D_MapRangeClamped(const FVector2D& InValue, const FVector2D& InRangeA, const FVector2D& InRangeB, const FVector2D& OutRangeA, const FVector2D& OutRangeB)
{
	return FVector2D
	(
		FMath::GetMappedRangeValueClamped(FVector2D(InRangeA.X, InRangeB.X), FVector2D(OutRangeA.X, OutRangeB.X), InValue.X),
		FMath::GetMappedRangeValueClamped(FVector2D(InRangeA.Y, InRangeB.Y), FVector2D(OutRangeA.Y, OutRangeB.Y), InValue.Y)
	);
}

FVector2D UBPFunctions_Math::Vector2D_MapRangeUnclamped(const FVector2D& InValue, const FVector2D& InRangeA, const FVector2D& InRangeB, const FVector2D& OutRangeA, const FVector2D& OutRangeB)
{
	return FVector2D
	(
		FMath::GetMappedRangeValueUnclamped(FVector2D(InRangeA.X, InRangeB.X), FVector2D(OutRangeA.X, OutRangeB.X), InValue.X),
		FMath::GetMappedRangeValueUnclamped(FVector2D(InRangeA.Y, InRangeB.Y), FVector2D(OutRangeA.Y, OutRangeB.Y), InValue.Y)
	);
}
