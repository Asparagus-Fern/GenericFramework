// Fill out your copyright notice in the Description page of Project Settings.

#include "Common/CommonActor.h"

ACommonActor::ACommonActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACommonActor::BeginPlay()
{
	Super::BeginPlay();
}
