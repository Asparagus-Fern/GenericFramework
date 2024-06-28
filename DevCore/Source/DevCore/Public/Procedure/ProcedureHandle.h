// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureType.h"
#include "UObject/Object.h"
#include "ProcedureHandle.generated.h"

class IProcedureInterface;

/**
 * 
 */
UCLASS()
class DEVCORE_API UProcedureHandle : public UObject
{
	GENERATED_BODY()

public:
	FSimpleMulticastDelegate OnHandleFinish;
	void Handle(const TArray<FProcedureInterfaceHandle>& InHandles);

protected:
	TArray<FProcedureInterfaceHandle> Handles;
	int32 HandleIndex = 0;
	FProcedureInterfaceHandle CurrentHandle;

	void HandleProcedure();
	
	void OnHandleOnceFinish_Internal();
	void OnHandleFinish_Internal();
};
