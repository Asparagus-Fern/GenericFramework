// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Procedure/ProcedureInterface.h"
#include "Debug/DebugType.h"

// #define GENERATE_STATIC_DELEGATE_TwoParams(ClassName, DelegateName, Param1Type, Param1Name, Param2Type, Param2Name) \
// 	DECLARE_EVENT_TwoParams(ClassName, F##DelegateName, Param1Type, Param2Type); \
// 	inline static F##DelegateName Delegate_##DelegateName; \
// 	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(F##DelegateName##_BP, Param1Type, Param1Name, Param2Type, Param2Name) \
// 	UPROPERTY(BlueprintAssignable,BlueprintCallable) \
// 	F##DelegateName##_BP BPDelegate_##DelegateName;

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
