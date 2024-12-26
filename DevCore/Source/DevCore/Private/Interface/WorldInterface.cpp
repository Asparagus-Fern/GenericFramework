// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/WorldInterface.h"

void IWorldInterface::InitializeWorldInterface()
{
	FWorldDelegates::OnPostWorldCreation.AddRaw(this, &IWorldInterface::HandleOnWorldCreationInternal);
	FWorldDelegates::OnWorldBeginTearDown.AddRaw(this, &IWorldInterface::HandleOnWorldBeginTearDownInternal);
}

IWorldInterface::~IWorldInterface()
{
}

void IWorldInterface::HandleOnWorldCreationInternal(UWorld* InWorld)
{
	FWorldDelegates::OnPostWorldCreation.RemoveAll(this);

	InWorld->OnWorldMatchStarting.AddRaw(this, &IWorldInterface::HandleOnWorldMatchStartingInternal, InWorld);
	InWorld->OnWorldBeginPlay.AddRaw(this, &IWorldInterface::HandleOnWorldBeginPlayInternal, InWorld);

	HandleOnWorldCreation(InWorld);
}

void IWorldInterface::HandleOnWorldBeginTearDownInternal(UWorld* InWorld)
{
	FWorldDelegates::OnWorldBeginTearDown.RemoveAll(this);

	HandleOnWorldEndPlay(InWorld);
}

void IWorldInterface::HandleOnWorldMatchStartingInternal(UWorld* InWorld)
{
	InWorld->OnWorldMatchStarting.RemoveAll(this);
	HandleOnWorldMatchStarting(InWorld);
}

void IWorldInterface::HandleOnWorldBeginPlayInternal(UWorld* InWorld)
{
	InWorld->OnWorldBeginPlay.RemoveAll(this);
	HandleOnWorldBeginPlay(InWorld);
}
