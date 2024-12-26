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
	void OnFlowRegister(UProcedureFlowComponent* InProcedureFlow);

	UFUNCTION(BlueprintNativeEvent, Category="Procedure Flow Interface")
	void OnFlowUnRegister(UProcedureFlowComponent* InProcedureFlow);
};
