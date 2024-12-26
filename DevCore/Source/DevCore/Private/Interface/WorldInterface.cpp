// Fill out your copyright notice in the Description page of Project Settings.


#include "Interface/WorldInterface.h"

void IWorldInterface::InitializeWorldInterface()
{
	FWorldDelegates::OnPostWorldCreation.AddRaw(this, &IWorldInterface::HandleOnWorldCreationInternal);
	FWorldDelegates::OnWorldBeginTearDown.AddRaw(this, &IWorldInterface::HandleOnWorldBeginTearDownInternal);
}

IWorldInterface::~IWorldInterface()
{
	FWorldDelegates::OnPostWorldCreation.RemoveAll(this);
	FWorldDelegates::OnWorldBeginTearDown.RemoveAll(this);
}

void IWorldInterface::HandleOnWorldCreationInternal(UWorld* InWorld)
{
	InWorld->OnWorldMatchStarting.AddRaw(this, &IWorldInterface::HandleOnWorldMatchStartingInternal, InWorld);
	InWorld->OnWorldBeginPlay.AddRaw(this, &IWorldInterface::HandleOnWorldBeginPlayInternal, InWorld);

	HandleOnWorldCreation(InWorld);
}

void IWorldInterface::HandleOnWorldBeginTearDownInternal(UWorld* InWorld)
{
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
