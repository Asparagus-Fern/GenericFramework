// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/TickableObject.h"

UWorld* UTickableObject::GetTickableGameObjectWorld() const
{
	return GetWorld();
}

ETickableTickType UTickableObject::GetTickableTickType() const
{
	return IsTemplate() ? ETickableTickType::Never : FTickableGameObject::GetTickableTickType();
}

bool UTickableObject::IsAllowedToTick() const
{
	return FTickableGameObject::IsAllowedToTick();
}

void UTickableObject::Tick(float DeltaTime)
{
	OnTick(DeltaTime);
}

TStatId UTickableObject::GetStatId() const
{
	return UCommonObject::GetStatID();
}

void UTickableObject::OnTick_Implementation(float DeltaTime)
{
}
