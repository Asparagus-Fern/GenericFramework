// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericThread.h"
// #include "GenericSingleThread.generated.h"

/**
 * 
 */
class GENERICTHREADSYSTEM_API FGenericSingleThread : public FGenericThread, public FSingleThreadRunnable
{
public:
	FGenericSingleThread(const FString& InThreadName = TEXT("GenericSingleThread"), uint32 InThreadSize = 0, EThreadPriority InThreadPriority = EThreadPriority::TPri_Normal);
	virtual ~FGenericSingleThread() override;

	static TSharedPtr<FGenericSingleThread> CreateThread(const FString& InThreadName, uint32 InThreadSize = 0, EThreadPriority InThreadPriority = EThreadPriority::TPri_Normal)
	{
		return MakeShareable(new FGenericSingleThread(InThreadName, InThreadSize, InThreadPriority));
	}

	/* FRunnable */
public:
	virtual FSingleThreadRunnable* GetSingleThreadInterface() override { return this; }

	/* FSingleThreadRunnable */
private:
	virtual void Tick() override;
};
