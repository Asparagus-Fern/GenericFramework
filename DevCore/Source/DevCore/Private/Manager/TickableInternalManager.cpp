// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/TickableInternalManager.h"

UWorld* FTickableInternalManager::GetTickableGameObjectWorld() const
{
	if (!GetManagerOwner())
	{
		return nullptr;
	}

	return GetManagerOwner()->GetWorld();;
}