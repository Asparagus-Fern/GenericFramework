// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Item/PickableItemComponent.h"

UPickableItemComponent::UPickableItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPickableItemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPickableItemComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
