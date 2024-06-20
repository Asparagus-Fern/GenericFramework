// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/DevPlayerController.h"

#include "Gameplay/Common/CommonPlayerCameraManager.h"

ADevPlayerController::ADevPlayerController()
{
	PlayerCameraManagerClass = ACommonPlayerCameraManager::StaticClass();
}
