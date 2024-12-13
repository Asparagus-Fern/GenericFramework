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

FGuid FCoreInternalManager::RegisterManager(UObject* InOwner)
{
	ManagerID = FGuid::NewGuid();

	if (IsValid(InOwner))
	{
		Owner = InOwner;
		UManagerProxy::Get()->RegisterManager(this);
		OnManagerInitialized();
	}
	else
	{
		DLOG(DLogManager, Error, TEXT("Regist Manager Fail, Must Provide Owner For Internal Manager"));
	}
	
	return ManagerID;
}

void FCoreInternalManager::UnRegisterManager()
{
	UManagerProxy::Get()->UnRegisterManager(this);
	OnManagerDeinitialized();
}

void FCoreInternalManager::OnManagerInitialized()
{
	DLOG(DLogManager, Log, TEXT("On Manager Initialized : %s"), *GetManagerOwner()->GetName());
}

void FCoreInternalManager::OnManagerDeinitialized()
{
	DLOG(DLogManager, Log, TEXT("On Manager Deinitialized : %s"), *GetManagerOwner()->GetName());
}

void FCoreInternalManager::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	DLOG(DLogManager, Log, TEXT("On Manager Match Starting : %s"), *GetManagerOwner()->GetName());
}

void FCoreInternalManager::HandleOnWorldBeginPlay(UWorld* InWorld)
{
	DLOG(DLogManager, Log, TEXT("On Manager Begin Play : %s"), *GetManagerOwner()->GetName());
}

void FCoreInternalManager::HandleOnWorldEndPlay(UWorld* InWorld)
{
	DLOG(DLogManager, Log, TEXT("On Manager End Play : %s"), *GetManagerOwner()->GetName());
}

UObject* FCoreInternalManager::GetManagerOwner() const
{
	return Owner;
}
