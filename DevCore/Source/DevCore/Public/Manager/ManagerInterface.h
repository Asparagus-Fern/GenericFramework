// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "ManagerInterface.generated.h"

class UManagerInfo;

/**
 * 
 */
class DEVCORE_API IManagerInterface
{
public:
	virtual ~IManagerInterface() = default;

public:
	virtual FGuid GetManagerID() const = 0;
	virtual FName GetManagerName() { return NAME_None; }
	virtual UObject* GetManagerOwner() const = 0;
	virtual int32 GetManagerOrder() { return 0; }
	
	virtual UManagerInfo* GetManagerInfo() { return nullptr; }

protected:
	virtual void OnManagerInitialized();
	virtual void OnManagerDeinitialized();
};
