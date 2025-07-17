// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Backpack/BackpackComponent.h"

UBackpackComponent::UBackpackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBackpackComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBackpackComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
