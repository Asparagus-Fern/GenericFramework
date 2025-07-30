// Copyright ChenTaiye 2025. All Rights Reserved.


#include "GameMode/GenericGameMode.h"

#include "GameState/GenericGameState.h"
#include "HUD/GenericHUD.h"
#include "Pawn/GenericPawn.h"
#include "PlayerController/GenericPlayerController.h"
#include "PlayerState/GenericPlayerState.h"

AGenericGameMode::AGenericGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = AGenericGameState::StaticClass();
	HUDClass = AGenericHUD::StaticClass();
	DefaultPawnClass = AGenericPawn::StaticClass();
	PlayerControllerClass = AGenericPlayerController::StaticClass();
	PlayerStateClass = AGenericPlayerState::StaticClass();
}

void AGenericGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	Players.Add(NewPlayer);
	OnPlayerLoginEvent.Broadcast(NewPlayer);
}

void AGenericGameMode::Logout(AController* Exiting)
{
	if (APlayerController* ExitPlayer = Cast<APlayerController>(Exiting))
	{
		OnPlayerLogoutEvent.Broadcast(ExitPlayer);
		Players.Remove(ExitPlayer);
	}

	Super::Logout(Exiting);
}
