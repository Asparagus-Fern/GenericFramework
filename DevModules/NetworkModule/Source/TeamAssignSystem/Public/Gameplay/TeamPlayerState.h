// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerState/DevPlayerState.h"
#include "TeamPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class TEAMASSIGNSYSTEM_API ATeamPlayerState : public ADevPlayerState
{
	GENERATED_BODY()

protected:
	virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
};
