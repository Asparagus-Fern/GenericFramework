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

	if (IsLocalController())
	{
		UGenericGameHUDManager::Delegate_PostHUDCreated.AddUObject(this, &AGenericPlayerController::NativeOnPlayerGameHUDCreated);
	}
}

void AGenericPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGenericPlayerController::NativeOnPlayerGameHUDCreated()
{
	UGenericGameHUDManager::Delegate_PostHUDCreated.RemoveAll(this);
	OnPlayerGameHUDCreated();
}
