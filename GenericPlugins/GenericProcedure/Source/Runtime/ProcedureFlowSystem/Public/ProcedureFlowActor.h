// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ProcedureFlowInterface.h"
#include "GameFramework/Actor.h"
#include "ProcedureFlowActor.generated.h"

class UProcedureFlowComponent;

UCLASS(Abstract, HideCategories=(Replication,Collision,HLOD,Physics,Networking,Cooking,Rendering), MinimalAPI)
class AProcedureFlowActor : public AActor, public IProcedureFlowInterface
{
	GENERATED_BODY()

public:
	PROCEDUREFLOWSYSTEM_API AProcedureFlowActor();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UProcedureFlowComponent* ProcedureFlowComponent = nullptr;
};
