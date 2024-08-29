// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_Object.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UBPFunctions_Object : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	template <typename T>
	static TSubclassOf<T> LoadClass(TSoftClassPtr<T> InSoftClassPtr)
	{
		if (InSoftClassPtr.IsPending())
		{
			return InSoftClassPtr.LoadSynchronous();
		}
		else
		{
			return InSoftClassPtr.Get();
		}
	}

	template <typename T>
	static T* LoadObject(TSoftObjectPtr<T> InSoftObjectPtr)
	{
		if (InSoftObjectPtr.IsPending())
		{
			return InSoftObjectPtr.LoadSynchronous();
		}
		else
		{
			return InSoftObjectPtr.Get();
		}
	}
};
