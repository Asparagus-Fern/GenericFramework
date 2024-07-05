// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ManagerSubsystem.h"

#include "Manager/CoreManager.h"
#include "Manager/ManagerGlobal.h"

bool UManagerSubsystem::bManagerSubsystemInitialize = false;

bool UManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	PostWorldInitializationHandle = FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UManagerSubsystem::OnPostWorldInitialization);
	WorldBeginTearDownHandle = FWorldDelegates::OnWorldBeginTearDown.AddUObject(this, &UManagerSubsystem::OnWorldBeginTearDown);

	if (!bManagerSubsystemInitialize)
	{
		bManagerSubsystemInitialize = true;
		FManagerDelegates::OnManagerSubsystemInitialize.Broadcast();
	}
}

void UManagerSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

UWorld* UManagerSubsystem::GetWorld() const
{
	if (IsValid(World))
	{
		return World;
	}

	return Super::GetWorld();
}

UManagerSubsystem* UManagerSubsystem::Get()
{
	return GEngine->GetEngineSubsystem<UManagerSubsystem>();
}

void UManagerSubsystem::OnPostWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues IVS)
{
	if (InWorld->IsGameWorld())
	{
		World = InWorld;
		WorldMatchStartingHandle = InWorld->OnWorldMatchStarting.AddUObject(this, &UManagerSubsystem::OnWorldMatchStarting);
	}
}

void UManagerSubsystem::OnWorldMatchStarting()
{
	World->OnWorldMatchStarting.Remove(WorldMatchStartingHandle);
	FManagerDelegates::PreManagerActived.Broadcast();

	ProcessManagersInOrder
	(
		true, [this](UCoreManager* InManager)
		{
			if (InManager->DoesSupportWorldType(World->WorldType))
			{
				InManager->NativeOnActived();
				FManagerDelegates::OnManagerActived.Broadcast(InManager);
			}
		}
	);

	ProcessManagers([this](UCoreManager* InManager)
		{
			InManager->NativeOnBeginPlay();
		}
	);

	FManagerDelegates::PostManagerActived.Broadcast();
}

void UManagerSubsystem::OnWorldBeginTearDown(UWorld* InWorld)
{
	if (InWorld->IsGameWorld())
	{
		FManagerDelegates::PreManagerInActived.Broadcast();

		ProcessManagers([this](UCoreManager* InManager)
			{
				InManager->NativeOnEndPlay();
			}
		);

		ProcessManagersInOrder
		(
			false, [this](UCoreManager* InManager)
			{
				if (InManager->DoesSupportWorldType(World->WorldType))
				{
					FManagerDelegates::OnManagerInActived.Broadcast(InManager);
					InManager->NativeOnInactived();
				}
			}
		);

		FManagerDelegates::PostManagerInActived.Broadcast();
	}
}

UCoreManager* UManagerSubsystem::RegisterManager(TSubclassOf<UCoreManager> InManagerClass)
{
	/* 不创建Core Manager */
	if (InManagerClass == UCoreManager::StaticClass())
	{
		DEBUG(Debug_Manager, Warning, TEXT("Core Manager is Abstract"))
		return nullptr;
	}

	UCoreManager* NewManager = NewObject<UCoreManager>(this, InManagerClass);

	/* 已被子类覆盖的，只刷新config */
	const UCoreManager* Manager = GetManager(InManagerClass, false);
	if (IsValid(Manager))
	{
		DEBUG(Debug_Manager, Warning, TEXT("Manager Has Register"))
		OverrideManagers.Add(NewManager);
		NewManager->TryUpdateDefaultConfigFile();
		return nullptr;
	}

	/* 创建Manager */
	Managers.Add(NewManager);
	NewManager->NativeOnCreate();
	FManagerDelegates::OnManagerRegister.Broadcast(NewManager);

	return NewManager;
}

void UManagerSubsystem::UnRegisterManager(TSubclassOf<UCoreManager> InManagerClass)
{
	UCoreManager* RemoveManager = GetManager(InManagerClass, true);
	if (IsValid(RemoveManager))
	{
		FManagerDelegates::OnManagerUnRegister.Broadcast(RemoveManager);
		RemoveManager->NativeOnDestroy();
		Managers.Remove(RemoveManager);
	}
}

bool UManagerSubsystem::IsManagerRegister(const TSubclassOf<UCoreManager> InManagerClass, const bool bAccurate)
{
	const UCoreManager* Manager = GetManager(InManagerClass, bAccurate);
	if (IsValid(Manager))
	{
		return true;
	}

	return false;
}

bool UManagerSubsystem::IsManagerActive(TSubclassOf<UCoreManager> InManagerClass, bool bAccurate)
{
	UCoreManager* Manager = GetManager(InManagerClass, bAccurate);
	if (IsValid(Manager) && Manager->GetIsActive())
	{
		return true;
	}

	return false;
}

UCoreManager* UManagerSubsystem::GetManager(TSubclassOf<UCoreManager> InManagerClass, bool bAccurate)
{
	for (const auto& Manager : Managers)
	{
		if (bAccurate)
		{
			if (Manager->GetClass() == InManagerClass)
			{
				return Manager;
			}
		}
		else
		{
			if (Manager->GetClass() == InManagerClass || Manager->GetClass()->IsChildOf(InManagerClass))
			{
				return Manager;
			}
		}
	}

	return nullptr;
}

TArray<UCoreManager*> UManagerSubsystem::GetManagers()
{
	return Managers;
}
