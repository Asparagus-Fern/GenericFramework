// Copyright ChenTaiye 2025. All Rights Reserved. 


#include "NetworkGameMode.h"

#include "NetworkGameState.h"
#include "NetworkPlayerController.h"
#include "NetworkPlayerState.h"

ANetworkGameMode::ANetworkGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = ANetworkGameState::StaticClass();
	PlayerControllerClass = ANetworkPlayerController::StaticClass();
	PlayerStateClass = ANetworkPlayerState::StaticClass();
}

APlayerController* ANetworkGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	return Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
}

void ANetworkGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}
