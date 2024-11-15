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
	virtual UWorld* GetTickableGameObjectWorld() const override;
	virtual bool IsTickable() const override { return false; }
	virtual bool IsTickableInEditor() const override { return false; }
	virtual bool IsTickableWhenPaused() const override { return false; }
	virtual void Tick(float DeltaTime) override { return; }

	/* FCoreInternalManager */
protected:
	void RegistManager(UObject* InOwner);
	void UnRegistManager();

	virtual void OnManagerInitialized();
	virtual void OnManagerDeinitialized();
	
	virtual void OnWorldMatchStarting(UWorld* InWorld);
	virtual void OnWorldBeginPlay(UWorld* InWorld);
	virtual void OnWorldEndPlay(UWorld* InWorld);

private:
	UObject* GetOwner() const;
	UObject* Owner = nullptr;
};
