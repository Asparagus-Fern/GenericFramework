// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CoreInternalManager.h"
#include "Subsystems/EngineSubsystem.h"
#include "GlobalTimerManager.generated.h"

/**
 * 
 */
UCLASS()
class DEVCORE_API UGlobalTimerManager : public UEngineSubsystem, public FCoreInternalManager
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
};
