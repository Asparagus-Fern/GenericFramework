// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUDManager.h"

bool UGameHUDManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGameHUDManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RegisterManager(this);
}

void UGameHUDManager::Deinitialize()
{
	Super::Deinitialize();
	UnRegisterManager();
}

bool UGameHUDManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}
