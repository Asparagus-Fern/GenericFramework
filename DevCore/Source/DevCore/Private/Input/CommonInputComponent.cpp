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
		InputHandle->Object = Object;
		InputHandles.Add(InputHandle);
		SetupInputHandleMapping(InputHandle);
	}
}

void UCommonInputComponent::SetupInputHandleMapping(UInputHandle* InputHandle)
{
	if (InputHandle->TriggerEvents.Contains(ETriggerEvent::Started))
	{
		BindAction(InputHandle->InputAction, ETriggerEvent::Started, InputHandle, &UInputHandle::NativeOnStarted);
	}
	if (InputHandle->TriggerEvents.Contains(ETriggerEvent::Ongoing))
	{
		BindAction(InputHandle->InputAction, ETriggerEvent::Ongoing, InputHandle, &UInputHandle::NativeOngoing);
	}
	if (InputHandle->TriggerEvents.Contains(ETriggerEvent::Triggered))
	{
		BindAction(InputHandle->InputAction, ETriggerEvent::Triggered, InputHandle, &UInputHandle::NativeOnTriggered);
	}
	if (InputHandle->TriggerEvents.Contains(ETriggerEvent::Canceled))
	{
		BindAction(InputHandle->InputAction, ETriggerEvent::Canceled, InputHandle, &UInputHandle::NativeOnCanceled);
	}
	if (InputHandle->TriggerEvents.Contains(ETriggerEvent::Completed))
	{
		BindAction(InputHandle->InputAction, ETriggerEvent::Completed, InputHandle, &UInputHandle::NativeOnCompleted);
	}
}
