// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Manager/ManagerProxy.h"

#include "Debug/DebugType.h"
#include "Manager/CoreInternalManager.h"
#include "Manager/GlobalManagerSettings.h"

UManagerProxy* UManagerProxy::Instance = nullptr;

UManagerProxy* UManagerProxy::GetManagerProxy()
{
	return UManagerProxy::Get();
}

UManagerProxy* UManagerProxy::InitializeManagerProxy()
{
	if (!Instance)
	{
		Instance = NewObject<UManagerProxy>();
		Instance->AddToRoot();
	}

	Instance->InitializeInternal();

	return Instance;
}

void UManagerProxy::DeInitializeManagerProxy()
{
}

UManagerProxy* UManagerProxy::Get()
{
	if (!Instance)
	{
		Instance = NewObject<UManagerProxy>();
		Instance->AddToRoot();
	}

	return Instance;
}

void UManagerProxy::RegisterManager(IManagerInterface* InManager)
{
	if (!UGlobalManagerSettings::Get()->bEnableAllManager)
	{
		GenericLOG(GenericLogManager, Log, TEXT("Disable Manager Register"))
		return;
	}

	if (!InManager)
	{
		GenericLOG(GenericLogManager, Error, TEXT("InManager Is NULL"))
		return;
	}

	if (IsManagerExist(InManager))
	{
		GenericLOG(GenericLogManager, Warning, TEXT("InManager Is Already Registed"))
		return;
	}

	UManagerInfo* NewManagerInfo = NewObject<UManagerInfo>();
	NewManagerInfo->AddToRoot();

	NewManagerInfo->InitializeManagerInfo(InManager);
	ManagerInfos.Add(NewManagerInfo);

	OnManagerRegister.Broadcast(NewManagerInfo);

	SortManagers();
	GenericLOG(GenericLogManager, Log, TEXT("%s"), *InManager->GetManagerOwner()->GetName());
}

void UManagerProxy::UnRegisterManager(const IManagerInterface* InManager)
{
	if (!InManager)
	{
		GenericLOG(GenericLogManager, Error, TEXT("InManager Is NULL"))
		return;
	}

	if (!IsManagerExist(InManager))
	{
		GenericLOG(GenericLogManager, Warning, TEXT("InManager Is Already UnRegisted"))
		return;
	}

	UManagerInfo* RemoveManagerInfo = GetManagerInfo(InManager);
	if (IsValid(RemoveManagerInfo))
	{
		OnManagerUnRegister.Broadcast(RemoveManagerInfo);

		ManagerInfos.Remove(RemoveManagerInfo);
		RemoveManagerInfo->RemoveFromRoot();
		RemoveManagerInfo->MarkAsGarbage();

		SortManagers();
		GenericLOG(GenericLogManager, Log, TEXT("%s"), *InManager->GetManagerOwner()->GetName());
	}
}

bool UManagerProxy::IsManagerExist(const IManagerInterface* InManager)
{
	return IsManagerExist(InManager->GetManagerID());
}

bool UManagerProxy::IsManagerExist(FGuid InManagerID)
{
	for (const auto& Manager : ManagerInfos)
	{
		if (Manager->GetManagerID() == InManagerID)
		{
			return true;
		}
	}

	return false;
}

void UManagerProxy::SortManagers()
{
	ManagerInfos.Sort([](UManagerInfo& A, UManagerInfo& B)
		{
			return A.GetManagerOrder() > B.GetManagerOrder();
		}
	);
}

UManagerInfo* UManagerProxy::GetManagerInfo(const IManagerInterface* InManager) const
{
	return GetManagerInfo(InManager->GetManagerID());
}

UManagerInfo* UManagerProxy::GetManagerInfo(FGuid ManagerID) const
{
	for (const auto& ManagerInfo : ManagerInfos)
	{
		if (ManagerInfo->GetManagerID() == ManagerID)
		{
			return ManagerInfo;
		}
	}
	return nullptr;
}

UManagerInfo* UManagerProxy::GetManagerInfo(FName ManagerName) const
{
	for (const auto& ManagerInfo : ManagerInfos)
	{
		if (ManagerInfo->GetManagerName() == ManagerName)
		{
			return ManagerInfo;
		}
	}
	return nullptr;
}

TArray<UManagerInfo*> UManagerProxy::GetManagerInfos()
{
	return ManagerInfos;
}

void UManagerProxy::InitializeInternal()
{
	if (bIsInitialize)
	{
		return;
	}

	bIsInitialize = true;
	InitializeWorldInterface();
}

void UManagerProxy::HandleOnWorldCreation(UWorld* InWorld)
{
	for (const auto& Manager : ManagerInfos)
	{
		static_cast<FCoreInternalManager*>(Manager->ManagerInterface)->HandleOnWorldCreation(InWorld);
	}
}

void UManagerProxy::HandleOnWorldBeginTearDown(UWorld* InWorld)
{
	for (const auto& Manager : ManagerInfos)
	{
		static_cast<FCoreInternalManager*>(Manager->ManagerInterface)->HandleOnWorldBeginTearDown(InWorld);
	}
}

void UManagerProxy::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	for (const auto& Manager : ManagerInfos)
	{
		static_cast<FCoreInternalManager*>(Manager->ManagerInterface)->HandleOnWorldMatchStarting(InWorld);
	}
}

void UManagerProxy::HandleOnWorldBeginPlay(UWorld* InWorld)
{
	for (const auto& Manager : ManagerInfos)
	{
		static_cast<FCoreInternalManager*>(Manager->ManagerInterface)->HandleOnWorldBeginPlay(InWorld);
	}
}

void UManagerProxy::HandleOnWorldEndPlay(UWorld* InWorld)
{
	for (const auto& Manager : ManagerInfos)
	{
		static_cast<FCoreInternalManager*>(Manager->ManagerInterface)->HandleOnWorldEndPlay(InWorld);
	}
}
