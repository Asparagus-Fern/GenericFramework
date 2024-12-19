// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Handle/HandleBase.h"
// #include "CoreHandleManager.generated.h"

/**
 * 
 */
class EVENTUTILITIES_API FHandleInterface
{
public:
	FHandleInterface() { return; }
	virtual ~FHandleInterface() = default;

	virtual UHandleBase* RegisterHandle(UObject* Outer, TSubclassOf<UHandleBase> InHandleClass) = 0;
	virtual UHandleBase* RegisterHandle(UObject* Outer, TSubclassOf<UHandleBase> InHandleClass, FGuid InHandleID) = 0;
	virtual UHandleBase* RegisterHandle(UObject* Outer, TSubclassOf<UHandleBase> InHandleClass, FName InHandleName) = 0;

	virtual void UnRegisterHandle(UHandleBase* InHandle) = 0;
	virtual void UnRegisterHandle(FGuid InHandleID) = 0;
	virtual void UnRegisterHandle(FName InHandleName) = 0;

	virtual bool IsHandleRegister(const UHandleBase* InHandle) = 0;
	virtual bool IsHandleRegister(FGuid InHandleID) = 0;
	virtual bool IsHandleRegister(FName InHandleName) = 0;

	virtual TArray<UHandleBase*> GetAllHandles() = 0;

	virtual UHandleBase* GetHandle(FGuid InHandleID) = 0;
	virtual UHandleBase* GetHandle(FName InHandleName) = 0;
};
