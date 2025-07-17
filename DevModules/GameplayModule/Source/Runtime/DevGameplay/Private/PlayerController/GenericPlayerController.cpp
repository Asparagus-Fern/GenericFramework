// Copyright ChenTaiye 2025. All Rights Reserved.

#include "PlayerController/GenericPlayerController.h"

#include "PlayerController/GenericPlayerCameraManager.h"

AGenericPlayerController::AGenericPlayerController()
{
	PlayerCameraManagerClass = AGenericPlayerCameraManager::StaticClass();
}
