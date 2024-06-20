// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureInterface.h"
#include "ProcedureManagerInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UProcedureManagerInterface : public UProcedureInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEVCORE_API IProcedureManagerInterface : public IProcedureInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Procedure Manager Interface")
	void PreProcedureSwitch(EGameplayProcedure InOldProcedure, EGameplayProcedure InNewProcedure);
	virtual void NativePreProcedureSwitch(EGameplayProcedure InOldProcedure, EGameplayProcedure InNewProcedure);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Procedure Manager Interface")
	void PostProcedureSwitch(EGameplayProcedure InProcedure);
	virtual void NativePostProcedureSwitch(EGameplayProcedure InProcedure);
};
