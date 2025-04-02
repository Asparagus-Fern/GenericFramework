// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericThread.h"
#include "Misc/SingleThreadRunnable.h"
// #include "GenericSingleThread.generated.h"

/**
 * 
 */
class DEVCORE_API FGenericSingleThread : public FGenericThread, public FSingleThreadRunnable
{
public:
public:
	FGenericSingleThread(bool InCreatePipe);
	virtual ~FGenericSingleThread() override;

	/* FRunnable */
public:
	virtual FSingleThreadRunnable* GetSingleThreadInterface() override { return this; }

	/* FSingleThreadRunnable */
private:
	virtual void Tick() override;
};
