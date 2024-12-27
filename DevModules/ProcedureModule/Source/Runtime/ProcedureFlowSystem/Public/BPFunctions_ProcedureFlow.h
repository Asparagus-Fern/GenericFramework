// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BPFunctions_ProcedureFlow.generated.h"

class AProcedureFlowActor;
class UProcedureFlowComponent;

/**
 * 
 */
UCLASS()
class PROCEDUREFLOWSYSTEM_API UBPFunctions_ProcedureFlow : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void RegisterFlowByActor(AProcedureFlowActor* InActor);

	UFUNCTION(BlueprintCallable)
	static void RegisterFlowByComponent(UProcedureFlowComponent* InComponent);

	UFUNCTION(BlueprintCallable)
	static void EnterProcedureFlowByActor(AProcedureFlowActor* InActor);

	UFUNCTION(BlueprintCallable)
	static void EnterProcedureFlowByComponent(UProcedureFlowComponent* InComponent);

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="Procedure.Flow"))
	static void EnterProcedureFlowByTag(FGameplayTag InFlowTag);

	UFUNCTION(BlueprintCallable)
	static void UnRegisterFlowByActor(AProcedureFlowActor* InActor);

	UFUNCTION(BlueprintCallable)
	static void UnRegisterFlowByComponent(UProcedureFlowComponent* InComponent);

public:
	UFUNCTION(BlueprintPure)
	static FGameplayTag GetCurrentFlowTag();

	UFUNCTION(BlueprintPure)
	static UProcedureFlowComponent* GetCurrentProcedureFlowComponent();

	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="Procedure.Flow"))
	static UProcedureFlowComponent* GetProcedureFlowComponent(FGameplayTag InFlowTag);

	UFUNCTION(BlueprintPure)
	static TArray<UProcedureFlowComponent*> GetProcedureFlowComponents();
};
