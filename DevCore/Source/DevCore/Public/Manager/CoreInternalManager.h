// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Procedure/ProcedureInterface.h"
#include "Debug/DebugType.h"

/**
 * 
 */
class DEVCORE_API FCoreInternalManager
{
	friend class UManagerProxy;

public:
	FCoreInternalManager();
	virtual ~FCoreInternalManager();

	/* FCoreInternalManager */
protected:
	FGuid RegisterManager(UObject* InOwner);
	void UnRegisterManager();

	virtual void OnManagerInitialized();
	virtual void OnManagerDeinitialized();

	virtual void HandleOnWorldMatchStarting(UWorld* InWorld);
	virtual void HandleOnWorldBeginPlay(UWorld* InWorld);
	virtual void HandleOnWorldEndPlay(UWorld* InWorld);

protected:
	UObject* GetManagerOwner() const;
	UObject* Owner = nullptr;
	FGuid ManagerID;
};
