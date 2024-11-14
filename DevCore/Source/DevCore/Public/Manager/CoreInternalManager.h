// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Procedure/ProcedureInterface.h"

/**
 * 
 */
class DEVCORE_API FCoreInternalManager : public FTickableGameObject
{
	friend class UManagerProxy;

public:
	FCoreInternalManager();
	virtual ~FCoreInternalManager() override;

	/* FTickableGameObject */
public:
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(FPreviewForceFeedbackEffect, STATGROUP_Tickables); }
	virtual UWorld* GetTickableGameObjectWorld() const override { return GetOwner()->GetWorld(); }
	virtual bool IsTickable() const override { return false; }
	virtual bool IsTickableInEditor() const override { return false; }
	virtual bool IsTickableWhenPaused() const override { return false; }
	virtual void Tick(float DeltaTime) override { return; }

protected:
	void RegistManager(UObject* InOwner);
	void UnRegistManager();

	virtual void OnManagerInitialized() { return; }
	virtual void OnManagerDeinitialized() { return; }

	virtual void OnManagerBeginPlay(UWorld* InWorld) { return; }
	virtual void OnManagerEndPlay(UWorld* InWorld) { return; }

private:
	UObject* GetOwner() const;
	UObject* Owner = nullptr;

	void HandleOnWorldBeginPlay(UWorld* InWorld);
	void HandleOnWorldEndPlay(UWorld* InWorld);
};
