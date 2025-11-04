// Copyright ChenTaiye 2025. All Rights Reserved.

#include "ProcedureFlowActor.h"

#include "ProcedureFlowComponent.h"


AProcedureFlowActor::AProcedureFlowActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ProcedureFlowComponent = CreateDefaultSubobject<UProcedureFlowComponent>("Procedure Flow Component");
	RootComponent = ProcedureFlowComponent;
}
