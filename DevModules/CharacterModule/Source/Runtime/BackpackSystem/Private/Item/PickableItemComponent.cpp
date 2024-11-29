// Fill out your copyright notice in the Description page of Project Settings.


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
