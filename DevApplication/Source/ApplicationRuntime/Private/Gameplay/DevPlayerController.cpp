// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/DevPlayerController.h"

#include "Override/DPlayerCameraManager.h"

ADevPlayerController::ADevPlayerController()
{
	PlayerCameraManagerClass = ADPlayerCameraManager::StaticClass();
}