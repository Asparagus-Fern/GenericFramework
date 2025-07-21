// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Interface/ManagerInterface.h"

#include "Manager/ManagerProxy.h"

bool FManagerInterface::GetManagerHandle(FManagerHandle& OutManagerHandle)
{
	return UManagerProxy::GetManagerProxy()->GetManagerHandle(ManagerID, OutManagerHandle);
}

void FManagerInterface::RegisterManager(UObject* InOwner)
{
	if (!UManagerProxy::GetManagerProxy()->RegisterManager(FManagerHandle(InOwner, this), ManagerID))
	{
		GenericLOG(GenericLogManager, Error, TEXT("Register Manager Fail"));
	}
}

void FManagerInterface::UnRegisterManager()
{
	if (!UManagerProxy::GetManagerProxy()->UnRegisterManager(ManagerID))
	{
		GenericLOG(GenericLogManager, Error, TEXT("UnRegister Manager Fail"));
	}
}
