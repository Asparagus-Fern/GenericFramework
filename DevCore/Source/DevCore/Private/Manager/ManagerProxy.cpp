// Copyright ChenTaiye 2025. All Rights Reserved.


#include "Manager/ManagerProxy.h"

#include "Debug/DebugType.h"
#include "Manager/CoreInternalManager.h"
#include "Manager/GlobalManagerSettings.h"

UManagerProxy* UManagerProxy::Instance = nullptr;

UManagerProxy* UManagerProxy::GetManagerProxy()
{
	if (!Instance)
	{
		Instance = NewObject<UManagerProxy>();
		Instance->AddToRoot();
		Instance->InitializeInternal();
	}

	return Instance;
}

bool UManagerProxy::ExistManager(const FGuid InManagerID) const
{
	return ManagerList.Contains(InManagerID);
}

bool UManagerProxy::ExistManager(const UObject* InManagerOwner) const
{
	TArray<FManagerHandle> ManagerHandles;
	ManagerList.GenerateValueArray(ManagerHandles);

	for (auto& ManagerHandle : ManagerHandles)
	{
		if (ManagerHandle.GetManagerOwner() == InManagerOwner)
		{
			return true;
		}
	}

	return false;
}

bool UManagerProxy::ExistManager(const TSubclassOf<UObject>& InManagerOwnerClass) const
{
	TArray<FManagerHandle> ManagerHandles;
	ManagerList.GenerateValueArray(ManagerHandles);

	for (auto& ManagerHandle : ManagerHandles)
	{
		if (ManagerHandle.GetManagerOwner()->GetClass() == InManagerOwnerClass)
		{
			return true;
		}
	}

	return false;
}

bool UManagerProxy::GetManagerHandle(const FGuid InManagerID, FManagerHandle& OutManagerHandle) const
{
	if (!ManagerList.Contains(InManagerID))
	{
		return false;
	}

	OutManagerHandle = ManagerList.FindRef(InManagerID);
	return true;
}

bool UManagerProxy::GetManagerOwner(FGuid InManagerID, UObject*& OutManagerOwner) const
{
	if (!ManagerList.Contains(InManagerID))
	{
		return false;
	}

	OutManagerOwner = ManagerList.FindRef(InManagerID).GetManagerOwner();
	return true;
}

bool UManagerProxy::GetManager(FGuid InManagerID, TSharedRef<FCoreInternalManager>& OutManager) const
{
	if (!ManagerList.Contains(InManagerID))
	{
		return false;
	}

	OutManager = ManagerList.FindRef(InManagerID).GetManager();
	return true;
}

TArray<FManagerHandle> UManagerProxy::GetAllManagerHandles() const
{
	TArray<FManagerHandle> Result;
	ManagerList.GenerateValueArray(Result);
	return Result;
}

/* ==================== IWorldInterface ==================== */

void UManagerProxy::HandleOnWorldCreation(UWorld* InWorld)
{
	for (auto& Manager : ManagerList)
	{
		Manager.Value.GetManager()->HandleOnWorldCreation(InWorld);
	}
}

void UManagerProxy::HandleOnWorldMatchStarting(UWorld* InWorld)
{
	for (const auto& Manager : ManagerList)
	{
		Manager.Value.GetManager()->HandleOnWorldMatchStarting(InWorld);
	}
}

void UManagerProxy::HandleOnWorldBeginPlay(UWorld* InWorld)
{
	for (const auto& Manager : ManagerList)
	{
		Manager.Value.GetManager()->HandleOnWorldBeginPlay(InWorld);
	}
}

void UManagerProxy::HandleOnWorldEndPlay(UWorld* InWorld)
{
	for (const auto& Manager : ManagerList)
	{
		Manager.Value.GetManager()->HandleOnWorldEndPlay(InWorld);
	}
}

void UManagerProxy::HandleOnWorldBeginTearDown(UWorld* InWorld)
{
	for (const auto& Manager : ManagerList)
	{
		Manager.Value.GetManager()->HandleOnWorldBeginTearDown(InWorld);
	}
}

/* ==================== UManagerProxy ==================== */
bool UManagerProxy::RegisterManager(const FManagerHandle& InManagerHandle, FGuid& OutManagerID)
{
	if (!UGlobalManagerSettings::Get()->bEnableAllManager)
	{
		GenericLOG(GenericLogManager, Log, TEXT("Disable Manager Register"))
		return false;
	}

	if (!InManagerHandle.CheckIsValid())
	{
		GenericLOG(GenericLogManager, Error, TEXT("InManager Is InValid"))
		return false;
	}

	if (ExistManager(InManagerHandle.GetManagerID()) || ExistManager(InManagerHandle.GetManagerOwner()->GetClass()))
	{
		GenericLOG(GenericLogManager, Warning, TEXT("InManager Is Already Register"))
		return false;
	}

	FGuid ManagerID = InManagerHandle.GetManagerID();
	OutManagerID = ManagerID;
	ManagerList.Add(ManagerID, InManagerHandle);

	InManagerHandle.GetManager()->OnManagerInitialized();
	OnManagerRegister.Broadcast(InManagerHandle);

	return true;
}

bool UManagerProxy::UnRegisterManager(FGuid InManagerID)
{
	if (!InManagerID.IsValid())
	{
		GenericLOG(GenericLogManager, Error, TEXT("InManagerID Is InValid"))
		return false;
	}

	if (!ExistManager(InManagerID))
	{
		GenericLOG(GenericLogManager, Warning, TEXT("InManager Is Already UnRegister"))
		return false;
	}

	FManagerHandle ManagerHandle;
	if (GetManagerHandle(InManagerID, ManagerHandle))
	{
		ManagerList.Remove(InManagerID);
		ManagerHandle.GetManager()->OnManagerDeinitialized();
		OnManagerUnRegister.Broadcast(ManagerHandle);

		return true;
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
	InitializeWorldInterface();
}
