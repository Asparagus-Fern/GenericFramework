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

UWorld* FCoreInternalManager::GetTickableGameObjectWorld() const
{
	if (!GetOwner())
	{
		return nullptr;
	}

	return GetOwner()->GetWorld();;
}

void FCoreInternalManager::RegistManager(UObject* InOwner)
{
	if (!IsValid(InOwner))
	{
		DLOG(DLogManager, Error, TEXT("Regist Manager Fail, Must Provide Owner For Internal Manager"));
		return;
	}

	Owner = InOwner;
	UManagerProxy::Get()->RegistManager(this);
	OnManagerInitialized();
}

void FCoreInternalManager::UnRegistManager()
{
	UManagerProxy::Get()->UnRegistManager(this);
	OnManagerDeinitialized();
}

void FCoreInternalManager::OnManagerInitialized()
{
	DLOG(DLogManager, Log, TEXT("On Manager Initialized : %s"), *GetOwner()->GetName());
}

void FCoreInternalManager::OnManagerDeinitialized()
{
	DLOG(DLogManager, Log, TEXT("On Manager Deinitialized : %s"), *GetOwner()->GetName());
}

void FCoreInternalManager::OnWorldMatchStarting(UWorld* InWorld)
{
	DLOG(DLogManager, Log, TEXT("On Manager Match Starting : %s"), *GetOwner()->GetName());
}

void FCoreInternalManager::OnWorldBeginPlay(UWorld* InWorld)
{
	DLOG(DLogManager, Log, TEXT("On Manager Begin Play : %s"), *GetOwner()->GetName());
}

void FCoreInternalManager::OnWorldEndPlay(UWorld* InWorld)
{
	DLOG(DLogManager, Log, TEXT("On Manager End Play : %s"), *GetOwner()->GetName());
}

UObject* FCoreInternalManager::GetOwner() const
{
	return Owner;
}
