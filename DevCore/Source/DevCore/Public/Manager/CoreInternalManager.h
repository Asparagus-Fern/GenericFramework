// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Debug/DebugType.h"
#include "Manager/ManagerInterface.h"
#include "Interface/WorldInterface.h"
#include "Procedure/ProcedureInterface.h"


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

	virtual int32 GetManagerOrder() override;
	
	/* IWorldInterface */
protected:
	virtual void HandleOnWorldCreation(UWorld* InWorld) override { return; }
	virtual void HandleOnWorldBeginTearDown(UWorld* InWorld) override { return; }

	virtual void HandleOnWorldMatchStarting(UWorld* InWorld) override { return; }
	virtual void HandleOnWorldBeginPlay(UWorld* InWorld) override { return; }
	virtual void HandleOnWorldEndPlay(UWorld* InWorld) override { return; }
};
