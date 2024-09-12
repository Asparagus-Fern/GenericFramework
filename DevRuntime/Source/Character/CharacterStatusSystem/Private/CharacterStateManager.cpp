// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterStateManager.h"

#include "CharacterStateManagerSetting.h"

bool UCharacterStateManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer) && UCharacterStateManagerSetting::Get()->bEnableSubsystem;
}
