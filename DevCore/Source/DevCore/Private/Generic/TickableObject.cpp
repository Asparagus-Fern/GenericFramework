// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Generic/TickableObject.h"

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
	return UGenericObject::GetStatID();
}
