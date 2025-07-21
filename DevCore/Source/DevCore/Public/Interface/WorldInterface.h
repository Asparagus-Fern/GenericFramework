// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
// #include "WorldInterface.generated.h"


/**
 * 
 */
class DEVCORE_API IWorldInterface
{
public:
	IWorldInterface();
	virtual ~IWorldInterface();

protected:
	virtual void HandleOnWorldCreation(UWorld* InWorld) { return; }
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) { return; }
	virtual void HandleOnWorldBeginPlay(UWorld* InWorld) { return; }
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) { return; }
	virtual void HandleOnWorldBeginTearDown(UWorld* InWorld) { return; }
};
