// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Actor/GenericActor.h"

AGenericActor::AGenericActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGenericActor::BeginPlay()
{
	Super::BeginPlay();
}

void AGenericActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
