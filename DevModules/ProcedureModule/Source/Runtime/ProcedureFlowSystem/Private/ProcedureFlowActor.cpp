// Fill out your copyright notice in the Description page of Project Settings.


#include "ProcedureFlowActor.h"


AProcedureFlowActor::AProcedureFlowActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProcedureFlowActor::BeginPlay()
{
	Super::BeginPlay();
}

void AProcedureFlowActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
