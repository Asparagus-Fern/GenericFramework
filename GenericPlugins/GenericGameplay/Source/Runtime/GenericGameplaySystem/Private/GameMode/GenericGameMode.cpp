// Copyright ChenTaiye 2025. All Rights Reserved.

#include "GameMode/GenericGameMode.h"

#include "GameSession/GenericGameSession.h"
#include "GameState/GenericGameState.h"
#include "HUD/GenericHUD.h"
#include "Pawn/GenericPawn.h"
#include "PlayerController/GenericPlayerController.h"
#include "PlayerState/GenericPlayerState.h"

AGenericGameMode::AGenericGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameSessionClass = AGenericGameSession::StaticClass();
	GameStateClass = AGenericGameState::StaticClass();
	HUDClass = AGenericHUD::StaticClass();
	DefaultPawnClass = AGenericPawn::StaticClass();
	PlayerControllerClass = AGenericPlayerController::StaticClass();
	PlayerStateClass = AGenericPlayerState::StaticClass();
}

APlayerController* AGenericGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* NewPC = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	Players.Add(NewPC);
	OnPlayerLoginEvent.Broadcast(NewPC);

	return NewPC;
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
