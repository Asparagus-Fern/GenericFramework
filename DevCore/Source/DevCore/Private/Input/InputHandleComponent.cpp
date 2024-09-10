// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputHandleComponent.h"

#include "Input/InputHandle.h"

UInputHandleComponent::UInputHandleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInputHandleComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UInputHandleComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInputHandleComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void UInputHandleComponent::GenerateInputHandles()
{
	InputHandles.Reset();
	for (auto& InputHandleClass : InputHandleClasses)
	{
		if (InputHandleClass)
		{
			InputHandles.Add(NewObject<UInputHandle>(this, InputHandleClass));
		}
	}
}
