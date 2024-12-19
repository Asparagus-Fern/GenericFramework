// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveNode/ActiveNode_Load.h"

#include "ActiveNodeSettings.h"
#include "ActiveNodeSubsystem.h"

AActiveNode_Load::AActiveNode_Load()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AActiveNode_Load::BeginPlay()
{
	Super::BeginPlay();
}
