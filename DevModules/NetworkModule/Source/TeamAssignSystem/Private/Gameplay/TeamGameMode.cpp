// Copyright ChenTaiye 2025. All Rights Reserved.

#include "Gameplay/TeamGameMode.h"

#include "Gameplay/TeamGameState.h"
#include "Gameplay/TeamPlayerController.h"
#include "Gameplay/TeamPlayerState.h"
#include "Gameplay/TeamCharacter.h"

ATeamGameMode::ATeamGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = ATeamGameState::StaticClass();
	DefaultPawnClass = ATeamCharacter::StaticClass();
	PlayerControllerClass = ATeamPlayerController::StaticClass();
	PlayerStateClass = ATeamPlayerState::StaticClass();
}

void ATeamGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (ATeamGameState* TeamGameState = Cast<ATeamGameState>(GameState))
	{
		TeamGameState->Server_LoginPlayer(NewPlayer->GetPlayerState<APlayerState>());
	}
}

void ATeamGameMode::Logout(AController* Exiting)
{
	if (ATeamGameState* TeamGameState = Cast<ATeamGameState>(GameState))
	{
		TeamGameState->Server_LogoutPlayer(Exiting->GetPlayerState<APlayerState>());
	}

	Super::Logout(Exiting);
}
