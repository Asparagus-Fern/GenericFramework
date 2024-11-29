// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerController/DevPlayerController.h"

#include "PlayerController/DPlayerCameraManager.h"

ADevPlayerController::ADevPlayerController()
{
	PlayerCameraManagerClass = ADPlayerCameraManager::StaticClass();
}
