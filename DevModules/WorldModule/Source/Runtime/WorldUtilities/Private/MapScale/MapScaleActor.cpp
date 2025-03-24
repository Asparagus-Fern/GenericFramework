// Copyright ChenTaiye 2025. All Rights Reserved.


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
