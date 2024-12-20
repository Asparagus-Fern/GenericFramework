// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Debug/DebugType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject/PropertyAccessUtil.h"
#include "BPFunctions_Property.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYUTILITIES_API UBPFunctions_Property : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template <typename T>
	bool GetValueOfType(const UObject* Target, const FName& PropertyName, T& OutValue)
	{
		const FProperty* NamedProperty = PropertyAccessUtil::FindPropertyByName(PropertyName, Target->GetClass());
		if (nullptr == NamedProperty)
		{
			DLOG(DLogProperty, Error, TEXT("Find Null Property Named: %s"), *(PropertyName.ToString()));
			return false;
		}

		const T* TempValue = NamedProperty->ContainerPtrToValuePtr<T>(Target);
		if (TempValue)
		{
			OutValue = *TempValue;
			return true;
		}

		return false;
	}

	template <typename T>
	bool SetValueOfType(UObject* Target, const FName& PropertyName, T InValue)
	{
		const FProperty* NamedProperty = PropertyAccessUtil::FindPropertyByName(PropertyName, Target->GetClass());
		if (nullptr == NamedProperty)
		{
			DLOG(DLogProperty, Error, TEXT("Find Null Property Named: %s"), *(PropertyName.ToString()));
			return false;
		}

		T* TargetPropertyAddress = NamedProperty->ContainerPtrToValuePtr<T>(Target);
		if (TargetPropertyAddress)
		{
			*TargetPropertyAddress = InValue;
			return true;
		}

		return false;
	}
};
