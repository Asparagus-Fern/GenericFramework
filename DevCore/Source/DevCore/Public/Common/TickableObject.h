// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonObject.h"
#include "Tickable.h"
#include "TickableObject.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEVCORE_API UTickableObject : public UCommonObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual UWorld* GetTickableGameObjectWorld() const override;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
};
