// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Interface/ManagerInterface.h"

#include "Manager/ManagerProxy.h"

bool FManagerInterface::GetManagerHandle(FManagerHandle& OutManagerHandle)
{
	return UManagerProxy::GetManagerProxy()->GetManagerHandle(ManagerID, OutManagerHandle);
}

void FManagerInterface::RegisterManager(UObject* InOwner)
{
	UManagerProxy::GetManagerProxy()->RegisterManager(FManagerHandle(InOwner, this), ManagerID);
}

void FManagerInterface::UnRegisterManager()
{
	UManagerProxy::GetManagerProxy()->UnRegisterManager(ManagerID);
}
