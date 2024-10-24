// Fill out your copyright notice in the Description page of Project Settings.


#include "MapScale/MapScaleActor.h"

AMapScaleActor::AMapScaleActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = SceneComponent;
}

void AMapScaleActor::BeginPlay()
{
	Super::BeginPlay();
}
