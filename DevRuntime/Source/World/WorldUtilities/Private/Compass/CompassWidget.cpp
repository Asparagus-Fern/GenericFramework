// Fill out your copyright notice in the Description page of Project Settings.


#include "Compass/CompassWidget.h"

#include "SceneManager.h"
#include "Kismet/GameplayStatics.h"

float UCompassWidget::GetPlayerPointToNorthAngle() const
{
	if (const USceneManager* SceneManager = GetManager<USceneManager>())
	{
		return SceneManager->GetPlayerPointToNorthAngle(UGameplayStatics::GetPlayerControllerID(GetOwningPlayer()));
	}

	return 0.f;
}

float UCompassWidget::GetPlayerPitchAngle() const
{
	return GetOwningPlayer()->PlayerCameraManager->GetCameraRotation().Pitch;
}

float UCompassWidget::GetUIPointToNorthAngle_Implementation()
{
	return GetPlayerPointToNorthAngle();
}
