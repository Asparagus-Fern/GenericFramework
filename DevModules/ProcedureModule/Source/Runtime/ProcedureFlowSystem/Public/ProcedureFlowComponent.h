// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "ProcedureFlowInterface.h"
#include "Components/ActorComponent.h"
#include "ProcedureFlowComponent.generated.h"

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_ProcedureFlow);

UCLASS(ClassGroup=(Developer), meta=(BlueprintSpawnableComponent))
class PROCEDUREFLOWSYSTEM_API UProcedureFlowComponent : public UActorComponent, public IProcedureFlowInterface
{
	GENERATED_BODY()

public:
	UProcedureFlowComponent();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(Categories="Procedure.Flow"))
	FGameplayTag FlowTag = FGameplayTag::EmptyTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ProcedureFlowInOrder = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ProcedureFlowOutOrder = 0;
};
