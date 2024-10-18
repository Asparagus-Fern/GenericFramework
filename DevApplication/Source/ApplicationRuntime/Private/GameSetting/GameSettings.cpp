// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSetting/GameSettings.h"

#include "Debug/DebugType.h"

UGameSettings* UGameSettings::Get()
{
	return GEngine ? CastChecked<UGameSettings>(GEngine->GetGameUserSettings()) : nullptr;
}