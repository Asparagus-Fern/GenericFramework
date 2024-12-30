// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "ProcedureFlowInterface.generated.h"

class UProcedureFlowComponent;

// This class does not need to be modified.
UINTERFACE()
class UProcedureFlowInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROCEDUREFLOWSYSTEM_API IProcedureFlowInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, Category="Procedure Flow Interface")
	void OnProcedureFlowRegister();

	UFUNCTION(BlueprintNativeEvent, Category="Procedure Flow Interface")
	void OnProcedureFlowInitialized();

	UFUNCTION(BlueprintNativeEvent, Category="Procedure Flow Interface")
	void OnProcedureFlowEnter();

	UFUNCTION(BlueprintNativeEvent, Category="Procedure Flow Interface")
	void ReInitProcedureFlow();
	
	UFUNCTION(BlueprintNativeEvent, Category="Procedure Flow Interface")
	void OnProcedureFlowExit();

	UFUNCTION(BlueprintNativeEvent, Category="Procedure Flow Interface")
	void OnProcedureFlowDeinitialize();

	UFUNCTION(BlueprintNativeEvent, Category="Procedure Flow Interface")
	void OnProcedureFlowUnRegister();
};
