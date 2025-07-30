// Copyright ChenTaiye 2025. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GenericGameMode.generated.h"

class IPlayerIdentityInterface;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerLogin, APlayerController*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerLogout, APlayerController*);

/**
 * 
 */
UCLASS()
class GENERICGAMEPLAYSYSTEM_API AGenericGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

public:
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;

public:
	TArray<APlayerController*> GetPlayers() { return Players; }
	static FOnPlayerLogin& GetOnPlayerLogin() { return OnPlayerLoginEvent; }
	static FOnPlayerLogout& GetOnPlayerLogout() { return OnPlayerLogoutEvent; }

private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<APlayerController>> Players;

	inline static FOnPlayerLogin OnPlayerLoginEvent;
	inline static FOnPlayerLogout OnPlayerLogoutEvent;
};
