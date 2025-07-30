// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interface/PlayerIdentityInterface.h"
#include "GenericPlayerController.generated.h"

class IPawnInputInterface;

/**
 * 
 */
UCLASS()
class GENERICGAMEPLAYSYSTEM_API AGenericPlayerController : public APlayerController, public IPlayerIdentityInterface
{
	GENERATED_BODY()

public:
	AGenericPlayerController();
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/* IPlayerIdentityInterface */
public:
	UFUNCTION(BlueprintPure)
	virtual int32 GetPlayerIdentity() override;

	UFUNCTION(BlueprintPure)
	virtual const FUniqueNetIdRepl& GetPlayerUniqueIdentity() override;
};
