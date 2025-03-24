// Copyright ChenTaiye 2025. All Rights Reserved.

#include "PlayerController/DevPlayerController.h"

#include "PlayerController/DPlayerCameraManager.h"

ADevPlayerController::ADevPlayerController()
{
	PlayerCameraManagerClass = ADPlayerCameraManager::StaticClass();
}
