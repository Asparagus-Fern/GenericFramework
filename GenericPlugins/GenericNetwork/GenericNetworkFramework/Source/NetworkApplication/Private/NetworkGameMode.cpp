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
