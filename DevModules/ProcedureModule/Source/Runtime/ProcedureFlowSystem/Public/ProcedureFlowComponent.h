// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "ProcedureFlowInterface.h"
#include "Components/ActorComponent.h"
#include "ProcedureFlowComponent.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureFlow);

UCLASS(ClassGroup=(Developer), meta=(BlueprintSpawnableComponent), MinimalAPI)
class UProcedureFlowComponent : public USceneComponent, public IProcedureFlowInterface
{
	GENERATED_BODY()

public:
	UProcedureFlowComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/* IProcedureFlowInterface */
public:
	virtual void OnProcedureFlowRegister_Implementation() override;
	virtual void OnProcedureFlowInitialized_Implementation() override;
	virtual void OnProcedureFlowEnter_Implementation() override;
	virtual void ReInitProcedureFlow_Implementation() override;
	virtual void OnProcedureFlowExit_Implementation() override;
	virtual void OnProcedureFlowDeinitialize_Implementation() override;
	virtual void OnProcedureFlowUnRegister_Implementation() override;

public:
	/* 是否手动注册 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bManualRegister = false;

	/* 即使Owner被隐藏也进行注册 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bRegisterEvenIsHidden = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Procedure.Flow"))
	FGameplayTag ProcedureFlowTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ProcedureFlowInitializedOrder = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ProcedureFlowDeinitializeOrder = 0;
};
