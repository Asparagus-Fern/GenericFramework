// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "StaticFunctions_Object.generated.h"

/**
 * 
 */
class UNREALMISC_API FStaticFunctions_Object
{
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
	static TArray<TSubclassOf<T>> LoadClass(const TArray<TSoftClassPtr<T>>& InSoftClasses)
	{
		TArray<TSubclassOf<T>> Result;
		for (auto& InSoftClass : InSoftClasses)
		{
			Result.Add(LoadClass(InSoftClass));
		}
		return Result;
	}

public:
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
