// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/CoreInternalManager.h"

#include "Manager/ManagerProxy.h"

FCoreInternalManager::FCoreInternalManager()
{
}

FCoreInternalManager::~FCoreInternalManager()
{
}

UManagerInfo* FCoreInternalManager::GetManagerInfo()
{
	return UManagerProxy::Get()->GetManagerInfo(this);
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
