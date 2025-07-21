// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Manager/ManagerType.h"

#include "Interface/ManagerInterface.h"

FManagerHandle::FManagerHandle()
{
}

FManagerHandle::FManagerHandle(UObject* InOwner, FManagerInterface* InManager)
	: ManagerOwner(InOwner),
	  Manager(InManager)
{
}

FManagerHandle::~FManagerHandle()
{
}

bool FManagerHandle::CheckIsValid() const
{
	return IsValid(ManagerOwner);
}

UObject* FManagerHandle::GetManagerOwner() const
{
	return ManagerOwner;
}

FGuid FManagerHandle::GetManagerID() const
{
	return ManagerID;
}

FManagerInterface* FManagerHandle::GetManager() const
{
	return Manager;
}
