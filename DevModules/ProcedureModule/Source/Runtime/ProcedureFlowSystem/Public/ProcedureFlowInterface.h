// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"
#include "ProcedureFlowInterface.generated.h"

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

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, Category="Procedure Flow Interface")
	void OnFlowRegister(FGameplayTag InFlowTag);

	UFUNCTION(BlueprintNativeEvent, Category="Procedure Flow Interface")
	void OnFlowUnRegister(FGameplayTag InFlowTag);
};
