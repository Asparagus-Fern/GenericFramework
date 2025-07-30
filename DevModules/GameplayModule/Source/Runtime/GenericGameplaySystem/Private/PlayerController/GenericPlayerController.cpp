// Copyright ChenTaiye 2025. All Rights Reserved.

#include "PlayerController/GenericPlayerController.h"

#include "GenericGameHUDManager.h"
#include "GameFramework/PlayerState.h"
#include "Manager/ManagerStatics.h"
#include "PlayerController/GenericPlayerCameraManager.h"

AGenericPlayerController::AGenericPlayerController()
{
	PlayerCameraManagerClass = AGenericPlayerCameraManager::StaticClass();
}

void AGenericPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AGenericPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

int32 AGenericPlayerController::GetPlayerIdentity()
{
	return GetPlayerState<APlayerState>()->GetPlayerId();
}

const FUniqueNetIdRepl& AGenericPlayerController::GetPlayerUniqueIdentity()
{
	return GetPlayerState<APlayerState>()->GetUniqueId();
}
