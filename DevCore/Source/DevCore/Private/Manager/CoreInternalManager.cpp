// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/CoreInternalManager.h"

#include "Debug/DebugType.h"
#include "Manager/ManagerProxy.h"

FCoreInternalManager::FCoreInternalManager()
{
}

FCoreInternalManager::~FCoreInternalManager()
{
}

void FCoreInternalManager::RegistManager(UObject* InOwner)
{
	Owner = InOwner;
	UManagerProxy::Get()->RegistManager(this);
	OnManagerInitialized();
	DLOG(DLogManager, Log, TEXT("On Initialized : %s"), *GetOwner()->GetName());

	if (UWorld* World = GetOwner()->GetWorld())
	{
		if (!World->IsGameWorld())
		{
			return;
		}

		if (World->bMatchStarted)
		{
			HandleOnWorldBeginPlay(World);
		}
		else
		{
			World->OnWorldMatchStarting.AddRaw(this, &FCoreInternalManager::HandleOnWorldBeginPlay, World);
		}

		FWorldDelegates::OnWorldBeginTearDown.AddRaw(this, &FCoreInternalManager::HandleOnWorldEndPlay);
	}
}

void FCoreInternalManager::UnRegistManager()
{
	UManagerProxy::Get()->UnRegistManager(this);
	OnManagerDeinitialized();
	DLOG(DLogManager, Log, TEXT("On Deinitialized : %s"), *GetOwner()->GetName());
}

UObject* FCoreInternalManager::GetOwner() const
{
	return Owner;
}

void FCoreInternalManager::HandleOnWorldBeginPlay(UWorld* InWorld)
{
	InWorld->OnWorldBeginPlay.RemoveAll(this);
	OnManagerBeginPlay(GetOwner()->GetWorld());
	DLOG(DLogManager, Log, TEXT("On Manager Begin Play : %s"), *GetOwner()->GetName());
}

void FCoreInternalManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	FWorldDelegates::OnWorldBeginTearDown.RemoveAll(this);
	OnManagerEndPlay(InWorld);
	DLOG(DLogManager, Log, TEXT("On Manager End Play : %s"), *GetOwner()->GetName());
}
