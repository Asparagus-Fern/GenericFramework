// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcedureFlowActor.h"

#include "ProcedureFlowComponent.h"


AProcedureFlowActor::AProcedureFlowActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ProcedureFlowComponent = CreateDefaultSubobject<UProcedureFlowComponent>("Procedure Flow Component");
	RootComponent = ProcedureFlowComponent;
}

void AProcedureFlowActor::BeginPlay()
{
	Super::BeginPlay();
}

void AProcedureFlowActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
