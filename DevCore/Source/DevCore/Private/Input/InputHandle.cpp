// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputHandle.h"

#include "Input/CommonInputComponent.h"

UInputHandle::UInputHandle()
{
	TriggerEvents.Add(ETriggerEvent::Started);
	TriggerEvents.Add(ETriggerEvent::Ongoing);
	TriggerEvents.Add(ETriggerEvent::Triggered);
	TriggerEvents.Add(ETriggerEvent::Canceled);
	TriggerEvents.Add(ETriggerEvent::Completed);
}

void UInputHandle::OnStarted_Implementation(UObject* InObject, const FInputActionValue& InValue)
{
}

void UInputHandle::SetupInputMapping(UObject* InObject, UCommonInputComponent* InInputComponent)
{
	if (!IsValid(InObject) || !IsValid(InInputComponent))
	{
		return;
	}

	Object = InObject;
	InputComponent = InInputComponent;

	if (TriggerEvents.Contains(ETriggerEvent::Started))
	{
		Handles.Add(InInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &UInputHandle::NativeOnStarted).GetHandle());
	}
	if (TriggerEvents.Contains(ETriggerEvent::Ongoing))
	{
		Handles.Add(InInputComponent->BindAction(InputAction, ETriggerEvent::Ongoing, this, &UInputHandle::NativeOngoing).GetHandle());
	}
	if (TriggerEvents.Contains(ETriggerEvent::Triggered))
	{
		Handles.Add(InInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &UInputHandle::NativeOnTriggered).GetHandle());
	}
	if (TriggerEvents.Contains(ETriggerEvent::Canceled))
	{
		Handles.Add(InInputComponent->BindAction(InputAction, ETriggerEvent::Canceled, this, &UInputHandle::NativeOnCanceled).GetHandle());
	}
	if (TriggerEvents.Contains(ETriggerEvent::Completed))
	{
		Handles.Add(InInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &UInputHandle::NativeOnCompleted).GetHandle());
	}
}

void UInputHandle::ClearupInputMapping()
{
	for (const auto& Handle : Handles)
	{
		InputComponent->RemoveActionBinding(Handle);
	}
}

void UInputHandle::NativeOnStarted(const FInputActionValue& InValue)
{
	if (IsValid(Object))
	{
		OnStarted(Object, InValue);
	}
}

void UInputHandle::Ongoing_Implementation(UObject* InObject, const FInputActionValue& InValue)
{
}

void UInputHandle::NativeOngoing(const FInputActionValue& InValue)
{
	if (IsValid(Object))
	{
		Ongoing(Object, InValue);
	}
}

void UInputHandle::OnTriggered_Implementation(UObject* InObject, const FInputActionValue& InValue)
{
}

void UInputHandle::NativeOnTriggered(const FInputActionValue& InValue)
{
	if (IsValid(Object))
	{
		OnTriggered(Object, InValue);
	}
}

void UInputHandle::OnCanceled_Implementation(UObject* InObject, const FInputActionValue& InValue)
{
}

void UInputHandle::NativeOnCanceled(const FInputActionValue& InValue)
{
	if (IsValid(Object))
	{
		OnCanceled(Object, InValue);
	}
}

void UInputHandle::OnCompleted_Implementation(UObject* InObject, const FInputActionValue& InValue)
{
}

void UInputHandle::NativeOnCompleted(const FInputActionValue& InValue)
{
	if (IsValid(Object))
	{
		OnCompleted(Object, InValue);
	}
}
