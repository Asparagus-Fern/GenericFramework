// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ManagerType.h"
#include "Debug/DebugType.h"
#include "Interface/WorldInterface.h"

#define BROADCAST_UNIFIED_DELEGATE(DelegateName, BPDelegateName, ...) \
	DelegateName.Broadcast(__VA_ARGS__); \
	BPDelegateName.Broadcast(__VA_ARGS__);

/**
 * 
 */
class DEVCORE_API FCoreInternalManager : public IWorldInterface
{
	friend class UManagerProxy;

public:
	FCoreInternalManager();
	virtual ~FCoreInternalManager() override;

	/* IWorldInterface */
protected:
	virtual void HandleOnWorldCreation(UWorld* InWorld) override { return; }
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override { return; } /* Initialize Manager, Bind Delegate... */
	virtual void HandleOnWorldBeginPlay(UWorld* InWorld) override { return; } /* Actor And Component Is Already BeginPlay */
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override { return; }
	virtual void HandleOnWorldBeginTearDown(UWorld* InWorld) override { return; }

	/* FCoreInternalManager */
public:
	virtual bool GetManagerHandle(FManagerHandle& OutManagerHandle);
	
protected:
	void RegisterManager(UObject* InOwner);
	void UnRegisterManager();

	virtual void OnManagerInitialized() { return; }
	virtual void OnManagerDeinitialized() { return; }

private:
	FGuid ManagerID;
};
