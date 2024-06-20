// Fill out your copyright notice in the Description page of Project Settings.

#include "ActiveNodeComponent.h"

// Sets default values for this component's properties
UActiveNodeComponent::UActiveNodeComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = false;
	bAutoActivate = true;
	bWantsInitializeComponent = true;
}

bool UActiveNodeComponent::CanUpdate_Implementation()
{
	return false;
}