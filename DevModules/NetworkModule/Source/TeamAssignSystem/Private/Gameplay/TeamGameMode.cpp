// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Gameplay/TeamGameMode.h"

#include "GenericGameHUDManager.h"
#include "Gameplay/TeamGameState.h"
#include "Gameplay/TeamPlayerController.h"
#include "Gameplay/TeamPlayerState.h"
#include "Gameplay/TeamCharacter.h"
#include "Manager/ManagerStatics.h"

ATeamGameMode::ATeamGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = ATeamGameState::StaticClass();
	DefaultPawnClass = ATeamCharacter::StaticClass();
	PlayerControllerClass = ATeamPlayerController::StaticClass();
	PlayerStateClass = ATeamPlayerState::StaticClass();
}
