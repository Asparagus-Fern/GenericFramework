// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ManagerInterface.h"

#include "Manager/ManagerProxy.h"

FGuid IManagerInterface::RegisterManager(UObject* InOwner)
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

void IManagerInterface::UnRegisterManager()
{
	UManagerProxy::Get()->UnRegisterManager(this);
	OnManagerDeinitialized();
}

void IManagerInterface::OnManagerInitialized()
{
}

void IManagerInterface::OnManagerDeinitialized()
{
}

UObject* IManagerInterface::GetManagerOwner() const
{
	return Owner;
}

FGuid IManagerInterface::GetManagerID() const
{
	return ManagerID;
}

int32 IManagerInterface::GetManagerOrder() 
{
	return 0;
}
