// Fill out your copyright notice in the Description page of Project Settings.


#include "BPFunctions/BPFunctions_Math.h"

FVector UBPFunctions_Math::Vector_Middle(FVector V1, FVector V2)
{
	return Vector_Middle_Alpha_Degrees(V1, V2, .5f, 0.f);
}

FVector UBPFunctions_Math::Vector_Middle_Degrees(FVector V1, FVector V2, float Degrees)
{
	return Vector_Middle_Alpha_Degrees(V1, V2, .5f, Degrees);
}

FVector UBPFunctions_Math::Vector_Middle_Radians(FVector V1, FVector V2, float Radians)
{
	return Vector_Middle_Alpha_Radians(V1, V2, .5f, Radians);
}

FVector UBPFunctions_Math::Vector_Middle_Alpha_Degrees(FVector V1, FVector V2, float Alpha, float Degrees)
{
	return (FRotator(0.f, FMath::Clamp(Degrees, -90.f, 90.f), 0.f).RotateVector((V2 - V1).GetSafeNormal(.0001f)))
		* ((FVector::Distance(V1, V2) * FMath::Clamp(Alpha, 0.f, 1.f)) / FMath::Cos(UE_DOUBLE_PI / (180.0) * Degrees))
		+ V1;
}

FVector UBPFunctions_Math::Vector_Middle_Alpha_Radians(FVector V1, FVector V2, float Alpha, float Radians)
{
	return Vector_Middle_Alpha_Degrees(V1, V2, Alpha, FMath::RadiansToDegrees(Radians));
}

FRotator UBPFunctions_Math::Rotator_Safe(FRotator R)
{
	return FRotator(R.Pitch, R.Yaw + R.Roll, 0.f);
}
