// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Manager/ManagerType.h"

#include "Manager/CoreInternalManager.h"

FManagerHandle::FManagerHandle()
{
	ManagerID = FGuid::NewGuid();
}

FManagerHandle::FManagerHandle(UObject* InOwner, const TSharedRef<FCoreInternalManager>& InManager)
	: ManagerOwner(InOwner),
	  Manager(InManager)
{
	ManagerID = FGuid::NewGuid();
}

bool FManagerHandle::CheckIsValid() const
{
	return IsValid(ManagerOwner) && Manager;
}

UObject* FManagerHandle::GetManagerOwner() const
{
	return ManagerOwner;
}

FGuid FManagerHandle::GetManagerID() const
{
	return ManagerID;
}

TSharedRef<FCoreInternalManager> FManagerHandle::GetManager() const
{
	return Manager.ToSharedRef();
}
