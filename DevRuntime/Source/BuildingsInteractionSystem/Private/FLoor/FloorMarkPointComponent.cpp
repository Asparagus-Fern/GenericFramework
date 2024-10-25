// Fill out your copyright notice in the Description page of Project Settings.


#include "Floor/FloorMarkPointComponent.h"

UFloorMarkPointComponent::FOnFloorMarkPointRefresh UFloorMarkPointComponent::OnFloorMarkPointRefresh;

UFloorMarkPointComponent::UFloorMarkPointComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFloorMarkPointComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFloorMarkPointComponent::OnRegister()
{
	Super::OnRegister();
	NativeOnRefresh();
}

void UFloorMarkPointComponent::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();
}
