// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcedureFlow/Load/ProcedureFlow_Load.h"

UE_DEFINE_GAMEPLAY_TAG(TAG_ProcedureFlow_Load, "Procedure.Flow.Load");

AProcedureFlow_Load::AProcedureFlow_Load()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProcedureFlow_Load::BeginPlay()
{
	Super::BeginPlay();
}

void AProcedureFlow_Load::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
