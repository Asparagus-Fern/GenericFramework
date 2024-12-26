// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureFlowInterface.h"
#include "GameFramework/Actor.h"
#include "ProcedureFlowActor.generated.h"

class UProcedureFlowComponent;

UCLASS()
class PROCEDUREFLOWSYSTEM_API AProcedureFlowActor : public AActor, public IProcedureFlowInterface
{
	GENERATED_BODY()

public:
	AProcedureFlowActor();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UProcedureFlowComponent* ProcedureFlowComponent = nullptr;
};
