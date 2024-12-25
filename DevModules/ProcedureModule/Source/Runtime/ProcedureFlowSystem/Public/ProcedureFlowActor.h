// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProcedureFlowActor.generated.h"

UCLASS()
class PROCEDUREFLOWSYSTEM_API AProcedureFlowActor : public AActor
{
	GENERATED_BODY()

public:
	AProcedureFlowActor();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
