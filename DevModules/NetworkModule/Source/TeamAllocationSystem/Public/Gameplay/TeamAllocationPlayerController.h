// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PlayerController/GenericPlayerController.h"

#include "TeamAllocationPlayerController.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI)
class ATeamAllocationPlayerController : public AGenericPlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	virtual void NativeOnPlayerGameHUDCreated() override;
};
