// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingsInteractionManager.h"

#include "BuildingsINteractionManagerSetting.h"

bool UBuildingsInteractionManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UBuildingsINteractionManagerSetting::Get()->bEnableSubsystem;
}

void UBuildingsInteractionManager::NativeOnActived()
{
	Super::NativeOnActived();
}

void UBuildingsInteractionManager::NativeOnInactived()
{
	Super::NativeOnInactived();
}
