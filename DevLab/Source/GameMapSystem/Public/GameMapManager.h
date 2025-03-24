// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameMapManager.generated.h"

class UGameMapInfo;

/**
 * 
 */
UCLASS()
class GAMEMAPSYSTEM_API UGameMapManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
};
