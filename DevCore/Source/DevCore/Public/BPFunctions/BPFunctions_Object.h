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
	static TSubclassOf<T> LoadClass(TSoftClassPtr<T> InSoftClass)
	{
		if (InSoftClass.IsPending())
		{
			return InSoftClass.LoadSynchronous();
		}
		else
		{
			return InSoftClass.Get();
		}
	}

	template <typename T>
	static TArray<TSubclassOf<T>> LoadClass(TArray<TSoftClassPtr<T>> InSoftClasses)
	{
		TArray<TSubclassOf<T>> Result;
		for (auto& InSoftClass : InSoftClasses)
		{
			Result.Add(LoadClass(InSoftClass));
		}
		return Result;
	}

	template <typename T>
	static T* LoadObject(TSoftObjectPtr<T> InSoftObject)
	{
		if (InSoftObject.IsPending())
		{
			return InSoftObject.LoadSynchronous();
		}
		else
		{
			return InSoftObject.Get();
		}
	}

	template <typename T>
	static TArray<T*> LoadObject(TArray<TSoftObjectPtr<T>> InSoftObjects)
	{
		TArray<T*> Result;
		for (auto& InSoftObject : InSoftObjects)
		{
			Result.Add(LoadObject(InSoftObject));
		}
		return Result;
	}
};
