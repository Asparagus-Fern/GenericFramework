// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/CommonInputComponent.h"

UCommonInputComponent::UCommonInputComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCommonInputComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCommonInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
