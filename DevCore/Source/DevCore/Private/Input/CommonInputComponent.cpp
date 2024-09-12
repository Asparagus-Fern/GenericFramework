// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/CommonInputComponent.h"

#include "Input/InputHandle.h"
#include "Input/InputHandleComponent.h"

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

void UCommonInputComponent::RegisterInputHandle(UInputHandleComponent* InputHandleComponent)
{
	if (IsValid(InputHandleComponent) && IsValid(InputHandleComponent->GetOwner()))
	{
		InputHandleComponent->GenerateInputHandles();
		for (const auto& InputHandle : InputHandleComponent->InputHandles)
		{
			RegisterInputHandle(InputHandleComponent->GetOwner(), InputHandle);
		}
	}
}

void UCommonInputComponent::RegisterInputHandle(UObject* Object, UInputHandle* InputHandle)
{
	if (IsValid(Object) && IsValid(InputHandle) && !InputHandles.Contains(InputHandle))
	{
		InputHandle->SetupInputMapping(Object, this);
		InputHandles.Add(InputHandle);
	}
}

void UCommonInputComponent::UnRegisterInputHandle(UInputHandleComponent* InputHandleComponent)
{
	if (IsValid(InputHandleComponent) && IsValid(InputHandleComponent->GetOwner()))
	{
		for (const auto& InputHandle : InputHandleComponent->InputHandles)
		{
			InputHandle->ClearupInputMapping();
		}
	}
}

void UCommonInputComponent::UnRegisterInputHandle(UInputHandle* InputHandle)
{
	if (IsValid(InputHandle) && InputHandles.Contains(InputHandle))
	{
		InputHandle->ClearupInputMapping();
		InputHandles.Remove(InputHandle);
	}
}
