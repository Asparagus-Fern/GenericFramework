// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureFlowInterface.h"
#include "Manager/ManagerProxy.h"
#include "Manager/ManagerStatics.h"
#include "GameFramework/Actor.h"
#include "ProcedureFlowActor.generated.h"

class UProcedureFlowComponent;

UCLASS(Abstract, HideCategories=(Replication,Collision,HLOD,Physics,Networking,Cooking,Rendering))
class PROCEDUREFLOWSYSTEM_API AProcedureFlowActor : public AActor, public IProcedureFlowInterface
{
	GENERATED_BODY()

public:
	AProcedureFlowActor();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UProcedureFlowComponent* ProcedureFlowComponent = nullptr;
};
