// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "WorldInterface.generated.h"

/**
 * 
 */
class DEVCORE_API FWorldInterface
{
public:
	void InitializeWorldInterface();
	virtual ~FWorldInterface() = default;

private:
	void HandleOnWorldCreationInternal(UWorld* InWorld);
	void HandleOnWorldBeginTearDownInternal(UWorld* InWorld);

protected:
	virtual void HandleOnWorldCreation(UWorld* InWorld) { return; }
	virtual void HandleOnWorldBeginTearDown(UWorld* InWorld) { return; }

	virtual void HandleOnWorldBeginPlay(UWorld* InWorld) { return; }
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) { return; }
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) { return; }
};
