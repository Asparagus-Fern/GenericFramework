// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "ProcedureFlowInterface.h"
#include "Components/ActorComponent.h"
#include "ProcedureFlowComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnProcedureFlowRegister, UProcedureFlowComponent*)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnProcedureFlowUnRegister, UProcedureFlowComponent*)

/**
 * 
 */
UCLASS(ClassGroup=(GenericFramework), meta=(BlueprintSpawnableComponent), MinimalAPI)
class UProcedureFlowComponent : public USceneComponent, public IProcedureFlowInterface
{
	GENERATED_BODY()

public:
	PROCEDUREFLOWSYSTEM_API virtual void BeginPlay() override;
	PROCEDUREFLOWSYSTEM_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	inline static FOnProcedureFlowRegister OnRegister;
	inline static FOnProcedureFlowUnRegister OnUnRegister;
	
	/* IProcedureFlowInterface */
public:
	PROCEDUREFLOWSYSTEM_API virtual void OnProcedureFlowRegister_Implementation() override;
	PROCEDUREFLOWSYSTEM_API virtual void OnProcedureFlowInitialized_Implementation() override;
	PROCEDUREFLOWSYSTEM_API virtual void OnProcedureFlowEnter_Implementation() override;
	PROCEDUREFLOWSYSTEM_API virtual void ReInitProcedureFlow_Implementation() override;
	PROCEDUREFLOWSYSTEM_API virtual void OnProcedureFlowExit_Implementation() override;
	PROCEDUREFLOWSYSTEM_API virtual void OnProcedureFlowDeinitialize_Implementation() override;
	PROCEDUREFLOWSYSTEM_API virtual void OnProcedureFlowUnRegister_Implementation() override;

public:
	/* 是否手动注册 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bManualRegister = false;

	/* 即使Owner被隐藏也进行注册 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bRegisterEvenIsHidden = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="ProcedureFlow"))
	FGameplayTag ProcedureFlowTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ProcedureFlowInitializedOrder = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ProcedureFlowDeinitializeOrder = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<TObjectPtr<class UProcedureFlowExecute>> ProcedureFlowExecutes;
};
