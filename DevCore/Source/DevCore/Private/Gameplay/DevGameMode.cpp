// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/DevGameMode.h"

#include "Gameplay/DevGameState.h"
#include "Gameplay/DevHUD.h"
#include "Gameplay/DevPlayerController.h"
#include "Gameplay/DevPlayerState.h"
#include "Pawn/DevPawn.h"

ADevGameMode::ADevGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GameStateClass = ADevGameState::StaticClass();
	HUDClass = ADevHUD::StaticClass();
	DefaultPawnClass = ADevPawn::StaticClass();
	PlayerControllerClass = ADevPlayerController::StaticClass();
	PlayerStateClass = ADevPlayerState::StaticClass();
}
