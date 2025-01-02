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
	static void RegisterProcedureFlowByActor(AProcedureFlowActor* InActor);

	UFUNCTION(BlueprintCallable)
	static void RegisterProcedureFlowByComponent(UProcedureFlowComponent* InComponent);

	UFUNCTION(BlueprintCallable)
	static void EnterProcedureFlowByActor(AProcedureFlowActor* InActor);

	UFUNCTION(BlueprintCallable)
	static void EnterProcedureFlowByComponent(UProcedureFlowComponent* InComponent);

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="Procedure.Flow"))
	static void EnterProcedureFlowByTag(FGameplayTag InProcedureFlowTag);

	UFUNCTION(BlueprintCallable)
	static void RefreshCurrentProcedureFlow();

	UFUNCTION(BlueprintCallable)
	static void ReEnterCurrentProcedureFlow();

	UFUNCTION(BlueprintCallable)
	static void ExitProcedureFlowByActor(AProcedureFlowActor* InActor);

	UFUNCTION(BlueprintCallable)
	static void ExitProcedureFlowByComponent(UProcedureFlowComponent* InComponent);

	UFUNCTION(BlueprintCallable, meta=(GameplayTagFilter="Procedure.Flow"))
	static void ExitProcedureFlowByTag(FGameplayTag InProcedureFlowTag);

	UFUNCTION(BlueprintCallable)
	static void UnRegisterProcedureFlowByActor(AProcedureFlowActor* InActor);

	UFUNCTION(BlueprintCallable)
	static void UnRegisterProcedureFlowByComponent(UProcedureFlowComponent* InComponent);

	UFUNCTION(BlueprintPure)
	static bool IsProcedureFlowActorActived(const AProcedureFlowActor* InActor);

	UFUNCTION(BlueprintPure)
	static bool IsProcedureFlowComponentActived(const UProcedureFlowComponent* InComponent);

	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="Procedure.Flow"))
	static bool IsProcedureFlowActived(FGameplayTag InProcedureFlowTag);

	UFUNCTION(BlueprintPure)
	static FGameplayTag GetCurrentProcedureFlowTag();

	UFUNCTION(BlueprintPure)
	static UProcedureFlowComponent* GetCurrentProcedureFlowComponent();

	UFUNCTION(BlueprintPure, meta = (DeterminesOutputType = "InClass"))
	static UProcedureFlowComponent* GetCurrentProcedureFlowComponentByClass(const TSubclassOf<UProcedureFlowComponent> InClass);

	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="Procedure.Flow"))
	static UProcedureFlowComponent* GetProcedureFlowComponent(FGameplayTag InProcedureFlowTag);

	UFUNCTION(BlueprintPure, meta=(GameplayTagFilter="Procedure.Flow", DeterminesOutputType = "InClass"))
	static UProcedureFlowComponent* GetProcedureFlowComponentByClass(FGameplayTag InProcedureFlowTag, const TSubclassOf<UProcedureFlowComponent> InClass);

	UFUNCTION(BlueprintPure)
	static TArray<UProcedureFlowComponent*> GetProcedureFlowComponents();
};
