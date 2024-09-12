// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMapManager.h"

#include "GameMapManagerSetting.h"

bool UGameMapManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UGameMapManagerSetting::Get()->bEnableSubsystem;;
}
