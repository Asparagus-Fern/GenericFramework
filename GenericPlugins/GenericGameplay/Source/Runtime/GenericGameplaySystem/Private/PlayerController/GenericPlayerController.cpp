// Copyright ChenTaiye 2025. All Rights Reserved.

#include "PlayerController/GenericPlayerController.h"

#include "GenericGameHUDSubsystem.h"

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
		UGenericGameHUDSubsystem::Delegate_PostHUDCreated.AddUObject(this, &AGenericPlayerController::NativeOnPlayerGameHUDCreated);
	}
}

void AGenericPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AGenericPlayerController::NativeOnPlayerGameHUDCreated()
{
	UGenericGameHUDSubsystem::Delegate_PostHUDCreated.RemoveAll(this);
	OnPlayerGameHUDCreated();
}
