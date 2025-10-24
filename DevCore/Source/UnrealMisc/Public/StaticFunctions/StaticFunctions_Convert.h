// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "StaticFunctions_Convert.generated.h"

/**
 * 
 */
class UNREALMISC_API FStaticFunctions_Convert
{
	/* To Bool */
public:
	static bool ToBool(unsigned int Var);

	/* To Int32 */
public:
	static int32 ToInt32(bool Var);
	static int32 ToInt32(uint8 Var);
	static int32 ToInt32(uint32 Var);
	static int32 ToInt32(int64 Var);
	static int32 ToInt32(FString Var);
	static int32 ToInt32(FName Var);
	static int32 ToInt32(FText Var);

	/* 四舍五入 */
	template <typename T>
	static FORCEINLINE int32 RoundToInt32(T Var) { return FMath::RoundToInt(Var); }

	/* 向上取整 */
	template <typename T>
	static FORCEINLINE int32 CeilToInt32(T Var) { return FMath::CeilToInt(Var); }

	/* 向下取整 */
	template <typename T>
	static FORCEINLINE int32 FloorToInt32(T Var) { return FMath::FloorToInt(Var); }

	/* To Int64 */
public:
	static int64 ToInt64(bool Var);
	static int64 ToInt64(uint8 Var);
	static int64 ToInt64(uint32 Var);
	static int64 ToInt64(int32 Var);
	static int64 ToInt64(FString Var);
	static int64 ToInt64(FName Var);
	static int64 ToInt64(FText Var);

	/* 四舍五入 */
	template <typename T>
	static FORCEINLINE int64 RoundToInt64(T Var) { return FMath::RoundToInt64(Var); }

	/* 向上取整 */
	template <typename T>
	static FORCEINLINE int64 CeilToInt64(T Var) { return FMath::CeilToInt(Var); }

	/* 向下取整 */
	template <typename T>
	static FORCEINLINE int64 FloorToInt64(T Var) { return FMath::FloorToInt(Var); }

	/* To Float */
public:
	static float ToFloat(bool Var);
	static float ToFloat(int32 Var);
	static float ToFloat(int64 Var);
	static float ToFloat(FString Var);
	static float ToFloat(FName Var);
	static float ToFloat(FText Var);

public:
	/* todo : to double/to FName/to FText... */

	/* To String */
public:
	static FString ToString(FString Var);
	static FString ToString(char* Var);
	static FString ToString(unsigned char* Var);
	static FString ToString(bool Var);
	static FString ToString(uint32 Var);
	static FString ToString(int32 Var);
	static FString ToString(int64 Var);
	static FString ToString(float Var);
	static FString ToString(double Var);
	static FString ToString(FName Var);
	static FString ToString(FText Var);
	static FString ToString(FVector Var);
	static FString ToString(FVector2D Var);
	static FString ToString(FRotator Var);
	static FString ToString(FTransform Var);
	static FString ToString(TArray<uint8> Var);

	/* To Byte Array */
public:
	static TArray<uint8> ToByteArray(const FString& InStr);
};
