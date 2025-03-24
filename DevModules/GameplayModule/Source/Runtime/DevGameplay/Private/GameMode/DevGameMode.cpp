// Copyright ChenTaiye 2025. All Rights Reserved.


#include "GameMode/DevGameMode.h"

#include "GameState/DevGameState.h"
#include "HUD/DevHUD.h"
#include "Pawn/DevPawn.h"
#include "PlayerController/DevPlayerController.h"
#include "PlayerState/DevPlayerState.h"

ADevGameMode::ADevGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = ADevGameState::StaticClass();
	HUDClass = ADevHUD::StaticClass();
	DefaultPawnClass = ADevPawn::StaticClass();
	PlayerControllerClass = ADevPlayerController::StaticClass();
	PlayerStateClass = ADevPlayerState::StaticClass();
}
