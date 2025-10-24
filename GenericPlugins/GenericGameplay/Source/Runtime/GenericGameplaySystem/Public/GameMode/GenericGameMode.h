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
UCLASS(MinimalAPI)
class AGenericGameMode : public AGameModeBase
{
	GENERATED_UCLASS_BODY()

public:
	GENERICGAMEPLAYSYSTEM_API virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	GENERICGAMEPLAYSYSTEM_API virtual void Logout(AController* Exiting) override;
	
public:
	GENERICGAMEPLAYSYSTEM_API TArray<APlayerController*> GetPlayers() { return Players; }
	GENERICGAMEPLAYSYSTEM_API static FOnPlayerLogin& GetOnPlayerLogin() { return OnPlayerLoginEvent; }
	GENERICGAMEPLAYSYSTEM_API static FOnPlayerLogout& GetOnPlayerLogout() { return OnPlayerLogoutEvent; }

private:
	UPROPERTY(Transient)
	TArray<TObjectPtr<APlayerController>> Players;

	inline static FOnPlayerLogin OnPlayerLoginEvent;
	inline static FOnPlayerLogout OnPlayerLogoutEvent;
};
