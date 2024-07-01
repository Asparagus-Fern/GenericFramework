// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureType.h"
#include "UObject/Object.h"
#include "ProcedureHandle.generated.h"

class IProcedureInterface;

/**
 * 流程处理的具体实现类，对使用了IProcedureInterface的类对象进行流程处理
 */
UCLASS()
class DEVCORE_API UProcedureHandle : public UObject
{
	GENERATED_BODY()

public:
	void Handle(const TArray<FProcedureInterfaceHandle>& InHandles);
	FSimpleMulticastDelegate GetHandleFinishDelegate() { return OnHandleFinish; }

protected:
	TArray<FProcedureInterfaceHandle> Handles;
	int32 HandleIndex = 0;
	FProcedureInterfaceHandle CurrentHandle;
	FSimpleMulticastDelegate OnHandleFinish;

	void HandleProcedure();
	void OnHandleOnceFinish_Internal();
	void OnHandleFinish_Internal();
};
