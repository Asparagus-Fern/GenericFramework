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
UCLASS(MinimalAPI)
class AGenericPlayerController : public APlayerController, public IPlayerIdentityInterface
{
	GENERATED_BODY()

public:
	GENERICGAMEPLAYSYSTEM_API AGenericPlayerController();
	GENERICGAMEPLAYSYSTEM_API virtual void BeginPlay() override;
	GENERICGAMEPLAYSYSTEM_API virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/* IPlayerIdentityInterface */
public:
	UFUNCTION(BlueprintPure)
	GENERICGAMEPLAYSYSTEM_API virtual int32 GetPlayerIdentity() override;

	UFUNCTION(BlueprintPure)
	GENERICGAMEPLAYSYSTEM_API virtual const FUniqueNetIdRepl& GetPlayerUniqueIdentity() override;

	/* AGenericPlayerController */
protected:
	GENERICGAMEPLAYSYSTEM_API virtual void NativeOnPlayerGameHUDCreated();
	UFUNCTION(BlueprintImplementableEvent)
	void OnPlayerGameHUDCreated();
};
