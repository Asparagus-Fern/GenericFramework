// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Interface/PlayerIdentityInterface.h"
#include "GenericPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GENERICGAMEPLAYSYSTEM_API AGenericPlayerState : public APlayerState, public IPlayerIdentityInterface
{
	GENERATED_BODY()

	/* IPlayerIdentityInterface */
public:
	UFUNCTION(BlueprintPure)
	virtual int32 GetPlayerIdentity() override;

	UFUNCTION(BlueprintPure)
	virtual const FUniqueNetIdRepl& GetPlayerUniqueIdentity() override;
};
