// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Debug/DebugType.h"
#include "Manager/ManagerInterface.h"
#include "Interface/WorldInterface.h"

#define BROADCAST_MANAGER_DELEGATE(DelegateName, BPDelegateName, ...) \
	DelegateName.Broadcast(__VA_ARGS__); \
	BPDelegateName.Broadcast(__VA_ARGS__);

/**
 * 
 */
class DEVCORE_API FCoreInternalManager : public IManagerInterface, public IWorldInterface
{
	friend class UManagerProxy;

public:
	FCoreInternalManager();
	virtual ~FCoreInternalManager() override;

	/* IManagerInterface */
protected:
	virtual void OnManagerInitialized() override { return; }
	virtual void OnManagerDeinitialized() override { return; }

	virtual FGuid GetManagerID() const override { return ManagerID; }
	virtual FName GetManagerName() override { return NAME_None; }
	virtual UObject* GetManagerOwner() const override { return Owner; }
	virtual int32 GetManagerOrder() override { return 0; }

	virtual UManagerInfo* GetManagerInfo() override;

	/* IWorldInterface */
protected:
	virtual void HandleOnWorldCreation(UWorld* InWorld) override { return; }
	virtual void HandleOnWorldBeginTearDown(UWorld* InWorld) override { return; }

	/* Call Only In Runtime */
protected:
	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override { return; } /* Initialize Manager, Bind Delegate... */
	virtual void HandleOnWorldBeginPlay(UWorld* InWorld) override { return; } /* Actor And Component Is Already BeginPlay */
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override { return; }

	/* FCoreInternalManager */
protected:
	UObject* Owner = nullptr;
	FGuid ManagerID;

	FGuid RegisterManager(UObject* InOwner);
	void UnRegisterManager();
};
