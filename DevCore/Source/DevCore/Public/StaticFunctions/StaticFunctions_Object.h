// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class DEVCORE_API FStaticFunctions_Object
{
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
