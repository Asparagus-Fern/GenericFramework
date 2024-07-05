// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureType.h"
#include "UObject/Object.h"
#include "ProcedureHandle.generated.h"

class UProcedureManager;
class IProcedureInterface;

/**
 * 流程处理的具体实现类，对使用了IProcedureInterface的类对象进行流程处理
 */
UCLASS(BlueprintType)
class DEVCORE_API UProcedureHandle : public UObject
{
	GENERATED_BODY()

	friend UProcedureManager;

public:
	void Reset();

protected:
	void Handle(const TArray<FProcedureInterfaceHandle>& InHandles, const FSimpleMulticastDelegate& InHandleFinish = FSimpleMulticastDelegate(), const FSimpleMulticastDelegate& InHandleReset = FSimpleMulticastDelegate());
	
	uint8 bReset : 1;
	TArray<FProcedureInterfaceHandle> Handles;
	int32 HandleIndex = 0;
	FProcedureInterfaceHandle CurrentHandle;

	FSimpleMulticastDelegate OnHandleReset;
	FSimpleMulticastDelegate OnHandleFinish;

	void HandleProcedure();
	void OnHandleOnceFinish_Internal();
	void OnHandleFinish_Internal();
};
