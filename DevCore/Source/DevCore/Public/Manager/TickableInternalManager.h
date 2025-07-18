// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Tickable.h"
#include "CoreInternalManager.h"

/**
 * 
 */
class DEVCORE_API FTickableInternalManager : public FCoreInternalManager, public FTickableGameObject
{
protected:
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(FTickableInternalManager, STATGROUP_Tickables); }
	virtual bool IsTickable() const override { return false; }
	virtual bool IsTickableInEditor() const override { return false; }
	virtual bool IsTickableWhenPaused() const override { return false; }
	virtual void Tick(float DeltaTime) override { return; }
};
