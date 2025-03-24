// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BuildingsInteractionManager.generated.h"

/**
 * 
 */
UCLASS()
class BUILDINGSINTERACTIONSYSTEM_API UBuildingsInteractionManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
};
