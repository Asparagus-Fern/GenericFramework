// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingsInteractionManager.h"

#include "BuildingsInteractionManagerSetting.h"

bool UBuildingsInteractionManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}
