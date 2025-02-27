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

void UTickableObject::Tick(float DeltaTime)
{
}

TStatId UTickableObject::GetStatId() const
{
	return UCommonObject::GetStatID();
}
