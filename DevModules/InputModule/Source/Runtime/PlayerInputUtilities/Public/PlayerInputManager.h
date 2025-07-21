// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystems.h"
#include "Interface/ManagerInterface.h"
#include "PlayerInputManager.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class UPlayerInputManager : public UEnhancedInputLocalPlayerSubsystem, public FManagerInterface
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
