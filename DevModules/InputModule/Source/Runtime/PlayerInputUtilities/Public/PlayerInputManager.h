// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "Manager/CoreInternalManager.h"
#include "PlayerInputManager.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UPlayerInputManager : public UEnhancedInputLocalPlayerSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
