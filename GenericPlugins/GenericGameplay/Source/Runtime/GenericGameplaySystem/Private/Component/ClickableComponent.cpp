// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/ClickableComponent.h"

UClickableComponent::UClickableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UClickableComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UClickableComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
