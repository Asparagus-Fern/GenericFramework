// Copyright ChenTaiye 2025. All Rights Reserved.

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
	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void RegisterProcedureFlowByActor(const UObject* WorldContextObject, AProcedureFlowActor* InActor);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void RegisterProcedureFlowByComponent(const UObject* WorldContextObject, UProcedureFlowComponent* InComponent);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void EnterProcedureFlowByActor(const UObject* WorldContextObject, AProcedureFlowActor* InActor);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void EnterProcedureFlowByComponent(const UObject* WorldContextObject, UProcedureFlowComponent* InComponent);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="ProcedureFlow"))
	static void EnterProcedureFlowByTag(const UObject* WorldContextObject, FGameplayTag InProcedureFlowTag);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void RefreshCurrentProcedureFlow(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void ReEnterCurrentProcedureFlow(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void ExitProcedureFlowByActor(const UObject* WorldContextObject, AProcedureFlowActor* InActor);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void ExitProcedureFlowByComponent(const UObject* WorldContextObject, UProcedureFlowComponent* InComponent);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="ProcedureFlow"))
	static void ExitProcedureFlowByTag(const UObject* WorldContextObject, FGameplayTag InProcedureFlowTag);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void UnRegisterProcedureFlowByActor(const UObject* WorldContextObject, AProcedureFlowActor* InActor);

	UFUNCTION(BlueprintCallable, meta=(WorldContext = "WorldContextObject"))
	static void UnRegisterProcedureFlowByComponent(const UObject* WorldContextObject, UProcedureFlowComponent* InComponent);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static bool IsProcedureFlowActorActived(const UObject* WorldContextObject, const AProcedureFlowActor* InActor);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static bool IsProcedureFlowComponentActived(const UObject* WorldContextObject, const UProcedureFlowComponent* InComponent);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="ProcedureFlow"))
	static bool IsProcedureFlowActived(const UObject* WorldContextObject, FGameplayTag InProcedureFlowTag);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static FGameplayTag GetCurrentProcedureFlowTag(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static UProcedureFlowComponent* GetCurrentProcedureFlowComponent(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject", DeterminesOutputType = "InClass"))
	static UProcedureFlowComponent* GetCurrentProcedureFlowComponentByClass(const UObject* WorldContextObject, const TSubclassOf<UProcedureFlowComponent> InClass);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="ProcedureFlow"))
	static UProcedureFlowComponent* GetProcedureFlowComponent(const UObject* WorldContextObject, FGameplayTag InProcedureFlowTag);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject", GameplayTagFilter="ProcedureFlow", DeterminesOutputType = "InClass"))
	static UProcedureFlowComponent* GetProcedureFlowComponentByClass(const UObject* WorldContextObject, FGameplayTag InProcedureFlowTag, const TSubclassOf<UProcedureFlowComponent> InClass);

	UFUNCTION(BlueprintPure, meta=(WorldContext = "WorldContextObject"))
	static TArray<UProcedureFlowComponent*> GetProcedureFlowComponents(const UObject* WorldContextObject);
};
