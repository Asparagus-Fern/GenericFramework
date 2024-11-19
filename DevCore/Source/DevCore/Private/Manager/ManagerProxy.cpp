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

void UManagerProxy::RegisterManager(FCoreInternalManager* InManager)
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

	ManagerMapping.Add(InManager->ManagerID, InManager);
}

void UManagerProxy::UnRegisterManager(FCoreInternalManager* InManager)
{
	if (!InManager)
	{
		DLOG(DLogManager, Error, TEXT("InManager Is NULL"))
		return;
	}

	if (ManagerMapping.Contains(InManager->ManagerID))
	{
		ManagerMapping.Remove(InManager->ManagerID);
	}
}

bool UManagerProxy::IsManagerExist(const FCoreInternalManager* InManager)
{
	return IsManagerExist(InManager->ManagerID);
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

void UManagerProxy::InitializeInternal()
{
	if (bIsInitialize)
	{
		return;
	}

	bIsInitialize = true;
	FWorldDelegates::OnPostWorldCreation.AddUObject(this, &UManagerProxy::HandleOnWorldCreation);
	FWorldDelegates::OnWorldBeginTearDown.AddUObject(this, &UManagerProxy::HandleOnWorldBeginTearDown);
}

void UManagerProxy::HandleOnWorldCreation(UWorld* InWorld)
{
	InWorld->OnWorldMatchStarting.AddUObject(this, &UManagerProxy::HandleOnWorldMatchStarting, InWorld);
	InWorld->OnWorldBeginPlay.AddUObject(this, &UManagerProxy::HandleOnWorldBeginPlay, InWorld);
}

void UManagerProxy::HandleOnWorldBeginTearDown(UWorld* InWorld)
{
	if (!InWorld->IsGameWorld())
	{
		return;
	}

	HandleOnWorldEndPlay(InWorld);
}

void UManagerProxy::HandleOnWorldBeginPlay(UWorld* InWorld)
{
	InWorld->OnWorldBeginPlay.RemoveAll(this);
	if (!InWorld->IsGameWorld())
	{
		return;
	}

	for (const auto& Manager : ManagerMapping)
	{
		Manager.Value->OnWorldBeginPlay(InWorld);
	}
}

void UManagerProxy::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	InWorld->OnWorldMatchStarting.RemoveAll(this);
	if (!InWorld->IsGameWorld())
	{
		return;
	}

	for (const auto& Manager : ManagerMapping)
	{
		Manager.Value->OnWorldMatchStarting(InWorld);
	}
}

void UManagerProxy::HandleOnWorldEndPlay(UWorld* InWorld)
{
	for (const auto& Manager : ManagerMapping)
	{
		Manager.Value->OnWorldEndPlay(InWorld);
	}
}
