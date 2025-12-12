// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ProcedureFlowActor.h"

#include "ProcedureFlowComponent.h"


AProcedureFlowActor::AProcedureFlowActor()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComponent;

	ProcedureFlowComponent = CreateDefaultSubobject<UProcedureFlowComponent>("Procedure Flow Component");
	ProcedureFlowComponent->SetupAttachment(RootComponent);
}
