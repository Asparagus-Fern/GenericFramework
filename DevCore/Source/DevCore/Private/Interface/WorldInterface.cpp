// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/WorldInterface.h"

void FWorldInterface::InitializeWorldInterface()
{
	FWorldDelegates::OnPostWorldCreation.AddRaw(this, &FWorldInterface::HandleOnWorldCreationInternal);
	FWorldDelegates::OnWorldBeginTearDown.AddRaw(this, &FWorldInterface::HandleOnWorldBeginTearDownInternal);
}

void FWorldInterface::HandleOnWorldCreationInternal(UWorld* InWorld)
{
	InWorld->OnWorldMatchStarting.AddRaw(this, &FWorldInterface::HandleOnWorldMatchStarting, InWorld);
	InWorld->OnWorldBeginPlay.AddRaw(this, &FWorldInterface::HandleOnWorldBeginPlay, InWorld);
}

void FWorldInterface::HandleOnWorldBeginTearDownInternal(UWorld* InWorld)
{
	if (!InWorld->IsGameWorld())
	{
		return;
	}

	HandleOnWorldEndPlay(InWorld);
}
