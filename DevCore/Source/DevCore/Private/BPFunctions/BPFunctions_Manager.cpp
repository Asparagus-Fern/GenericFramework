// Copyright ChenTaiye 2025. All Rights Reserved.


#include "BPFunctions/BPFunctions_Manager.h"

#include "Manager/ManagerActor.h"
#include "Manager/ManagerProxy.h"

UManagerProxy* UBPFunctions_Manager::GetManagerProxy()
{
	return UManagerProxy::Get();
}

UManagerInfo* UBPFunctions_Manager::GetManagerInfo(FName InManagerName)
{
	return UManagerProxy::Get()->GetManagerInfo(InManagerName);
}

TArray<UManagerInfo*> UBPFunctions_Manager::GetManagerInfos()
{
	return UManagerProxy::Get()->GetManagerInfos();
}
