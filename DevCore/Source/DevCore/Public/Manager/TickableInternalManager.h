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
	/* FTickableGameObject */
public:
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(FPreviewForceFeedbackEffect, STATGROUP_Tickables); }
	virtual UWorld* GetTickableGameObjectWorld() const override;
	virtual bool IsTickable() const override { return false; }
	virtual bool IsTickableInEditor() const override { return false; }
	virtual bool IsTickableWhenPaused() const override { return false; }
	virtual void Tick(float DeltaTime) override { return; }
};
