// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GenericObject.h"
#include "Tickable.h"
#include "TickableObject.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEVCORE_API UTickableObject : public UGenericObject, public FTickableGameObject
{
	GENERATED_BODY()

public:
	virtual UWorld* GetTickableGameObjectWorld() const override;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
};
