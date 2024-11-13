// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/DEnhancedInputComponent.h"

UDEnhancedInputComponent::UDEnhancedInputComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDEnhancedInputComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDEnhancedInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
