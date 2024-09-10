// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/InputHandle.h"

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
