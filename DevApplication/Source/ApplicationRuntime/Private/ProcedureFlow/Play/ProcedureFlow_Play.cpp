// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcedureFlow/Play/ProcedureFlow_Play.h"


AProcedureFlow_Play::AProcedureFlow_Play()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProcedureFlow_Play::OnProcedureFlowEnter_Implementation()
{
	Super::OnProcedureFlowEnter_Implementation();
}

void AProcedureFlow_Play::OnProcedureFlowExit_Implementation()
{
	Super::OnProcedureFlowExit_Implementation();
}
