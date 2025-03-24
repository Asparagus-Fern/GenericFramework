// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Manager/TickableInternalManager.h"

UWorld* FTickableInternalManager::GetTickableGameObjectWorld() const
{
	if (!GetManagerOwner())
	{
		return nullptr;
	}

	return GetManagerOwner()->GetWorld();;
}