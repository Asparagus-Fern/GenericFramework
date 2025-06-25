// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "StaticFunctions_Enum.generated.h"

/**
 * 
 */
class UNREALMISC_API FStaticFunctions_Enum
{
public:
	template <typename EnumType>
	static int64 GetEnumValue(EnumType InEnum)
	{
		const UEnum* EnumPtr = StaticEnum<EnumType>();
		const int32 Index = static_cast<int32>(InEnum);

		return EnumPtr->GetValueByIndex(Index);
	}

	template <typename EnumType>
	static bool GetEnumByValue(int64 InValue, EnumType& OutEnum)
	{
		if (InValue != INDEX_NONE)
		{
			OutEnum = static_cast<EnumType>(InValue);
			return true;
		}
		return false;
	}

	template <typename EnumType>
	static FName GetEnumName(EnumType InEnum)
	{
		const UEnum* EnumPtr = StaticEnum<EnumType>();
		const int32 Index = static_cast<int32>(InEnum);

		return EnumPtr->GetNameByIndex(Index);
	}

	template <typename EnumType>
	static bool GetEnumByName(FName InName, EnumType& OutEnum)
	{
		if (InName != NAME_None)
		{
			const UEnum* EnumPtr = StaticEnum<EnumType>();
			int64 Value = EnumPtr->GetValueByName(InName);

			return GetEnumByValue(Value, OutEnum);
		}
		return false;
	}

	template <typename EnumType>
	static FString GetEnumNameString(EnumType InEnum)
	{
		const UEnum* EnumPtr = StaticEnum<EnumType>();
		const int32 Index = static_cast<int32>(InEnum);

		return EnumPtr->GetNameStringByIndex(Index);
	}

	template <typename EnumType>
	static bool GetEnumByNameString(FString InNameString, EnumType& OutEnum)
	{
		if (!InNameString.IsEmpty())
		{
			const UEnum* EnumPtr = StaticEnum<EnumType>();
			int64 Value = EnumPtr->GetValueByNameString(InNameString);

			return GetEnumByValue(Value, OutEnum);
		}
		return false;
	}

	template <typename EnumType>
	static FText GetEnumDisplayNameText(EnumType InEnum)
	{
		const UEnum* EnumPtr = StaticEnum<EnumType>();
		const int32 Index = static_cast<int32>(InEnum);

		return EnumPtr->GetDisplayNameTextByIndex(Index);
	}

	template <typename EnumType>
	static FText GetEnumTooltipText(EnumType InEnum)
	{
		const UEnum* EnumPtr = StaticEnum<EnumType>();
		const int32 Index = static_cast<int32>(InEnum);

		return EnumPtr->GetToolTipTextByIndex(Index);
	}
};
