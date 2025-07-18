// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Manager/CoreInternalManager.h"

#include "Manager/ManagerProxy.h"

FCoreInternalManager::FCoreInternalManager()
{
}

FCoreInternalManager::~FCoreInternalManager()
{
}

bool FCoreInternalManager::GetManagerHandle(FManagerHandle& OutManagerHandle)
{
	return UManagerProxy::GetManagerProxy()->GetManagerHandle(ManagerID, OutManagerHandle);
}

void FCoreInternalManager::RegisterManager(UObject* InOwner)
{
	if (!UManagerProxy::GetManagerProxy()->RegisterManager(FManagerHandle(InOwner, MakeShareable(this)), ManagerID))
	{
		GenericLOG(GenericLogManager, Error, TEXT("Register Manager Fail"));
	}
}

void FCoreInternalManager::UnRegisterManager()
{
	if (!UManagerProxy::GetManagerProxy()->UnRegisterManager(ManagerID))
	{
		GenericLOG(GenericLogManager, Error, TEXT("UnRegister Manager Fail"));
	}
}
