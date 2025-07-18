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
	void InitializeWorldInterface();
	virtual ~IWorldInterface();

private:
	void HandleOnWorldCreationInternal(UWorld* InWorld);
	void HandleOnWorldBeginTearDownInternal(UWorld* InWorld);

	void HandleOnWorldMatchStartingInternal(UWorld* InWorld);
	void HandleOnWorldBeginPlayInternal(UWorld* InWorld);

protected:
	virtual void HandleOnWorldCreation(UWorld* InWorld) { return; }
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) { return; }
	virtual void HandleOnWorldBeginPlay(UWorld* InWorld) { return; }
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) { return; }
	virtual void HandleOnWorldBeginTearDown(UWorld* InWorld) { return; }
};
