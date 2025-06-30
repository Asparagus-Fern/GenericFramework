// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/DevGameMode.h"
#include "TeamGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TEAMASSIGNSYSTEM_API ATeamGameMode : public ADevGameMode
{
	GENERATED_UCLASS_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
};
