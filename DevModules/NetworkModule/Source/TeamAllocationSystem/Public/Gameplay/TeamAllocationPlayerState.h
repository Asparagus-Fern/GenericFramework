// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerState/GenericPlayerState.h"
#include "TeamAllocationPlayerState.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class ATeamAllocationPlayerState : public AGenericPlayerState
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
