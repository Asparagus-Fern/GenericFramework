// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "ManagerInterface.generated.h"

/**
 * 
 */
class DEVCORE_API IManagerInterface
{
public:
	virtual ~IManagerInterface() = default;

public:
	FGuid RegisterManager(UObject* InOwner);
	void UnRegisterManager();

	UObject* GetManagerOwner() const;
	FGuid GetManagerID() const;
	virtual int32 GetManagerOrder();

protected:
	virtual void OnManagerInitialized();
	virtual void OnManagerDeinitialized();

protected:
	UObject* Owner = nullptr;
	FGuid ManagerID;
};
