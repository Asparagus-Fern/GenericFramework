// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ManagerProxy.h"

#include "Debug/DebugType.h"
#include "Manager/CoreInternalManager.h"

UManagerProxy* UManagerProxy::Instance = nullptr;

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
	if (!InManager)
	{
		DLOG(DLogManager, Error, TEXT("InManager Is NULL"))
		return;
	}

	if (IsManagerExist(InManager))
	{
		DLOG(DLogManager, Warning, TEXT("InManager Is Already Registed"))
		return;
	}

	ManagerMapping.Add(InManager->GetManagerID(), InManager);
	SortManagers();

	DLOG(DLogManager, Log, TEXT("%s"), *InManager->GetManagerOwner()->GetName());
}

void UManagerProxy::UnRegisterManager(IManagerInterface* InManager)
{
	if (!InManager)
	{
		DLOG(DLogManager, Error, TEXT("InManager Is NULL"))
		return;
	}

	if (!IsManagerExist(InManager))
	{
		DLOG(DLogManager, Warning, TEXT("InManager Is Already UnRegisted"))
		return;
	}

	ManagerMapping.Remove(InManager->GetManagerID());
	SortManagers();

	DLOG(DLogManager, Log, TEXT("%s"), *InManager->GetManagerOwner()->GetName());
}

bool UManagerProxy::IsManagerExist(const IManagerInterface* InManager)
{
	return IsManagerExist(InManager->GetManagerID());
}

bool UManagerProxy::IsManagerExist(FGuid InManagerID)
{
	for (const auto& Manager : ManagerMapping)
	{
		if (Manager.Key == InManagerID)
		{
			return true;
		}
	}

	return false;
}

void UManagerProxy::SortManagers()
{
	ManagerMapping.ValueSort([](IManagerInterface& A, IManagerInterface& B)
		{
			return A.GetManagerOrder() > B.GetManagerOrder();
		}
	);
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
	for (const auto& Manager : ManagerMapping)
	{
		static_cast<FCoreInternalManager*>(Manager.Value)->HandleOnWorldCreation(InWorld);
	}
}

void UManagerProxy::HandleOnWorldBeginTearDown(UWorld* InWorld)
{
	for (const auto& Manager : ManagerMapping)
	{
		static_cast<FCoreInternalManager*>(Manager.Value)->HandleOnWorldBeginTearDown(InWorld);
	}
}

void UManagerProxy::HandleOnWorldBeginPlay(UWorld* InWorld)
{
	for (const auto& Manager : ManagerMapping)
	{
		static_cast<FCoreInternalManager*>(Manager.Value)->HandleOnWorldBeginPlay(InWorld);
	}
}

void UManagerProxy::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	for (const auto& Manager : ManagerMapping)
	{
		static_cast<FCoreInternalManager*>(Manager.Value)->HandleOnWorldMatchStarting(InWorld);
	}
}

void UManagerProxy::HandleOnWorldEndPlay(UWorld* InWorld)
{
	for (const auto& Manager : ManagerMapping)
	{
		static_cast<FCoreInternalManager*>(Manager.Value)->HandleOnWorldEndPlay(InWorld);
	}
}
