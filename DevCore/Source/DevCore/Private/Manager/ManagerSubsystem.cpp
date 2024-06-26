// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/ManagerSubsystem.h"

#include "Manager/CoreManager.h"

bool UManagerSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	PostWorldInitializationHandle = FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UManagerSubsystem::OnPostWorldInitialization);
	WorldBeginTearDownHandle = FWorldDelegates::OnWorldBeginTearDown.AddUObject(this, &UManagerSubsystem::OnWorldBeginTearDown);
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

	ProcessManagers([](UCoreManager* InManager)
		{
			InManager->NativeOnActived();
		}
	);
}

void UManagerSubsystem::OnWorldBeginTearDown(UWorld* InWorld)
{
	ProcessManagers([](UCoreManager* InManager)
		{
			InManager->NativeOnInactived();
		}
	);

	World = nullptr;
}

UCoreManager* UManagerSubsystem::RegisterManager(TSubclassOf<UCoreManager> InManagerClass)
{
	if (IsManagerRegister(InManagerClass, true))
	{
		return nullptr;
	}

	if (InManagerClass == UCoreManager::StaticClass())
	{
		return nullptr;
	}

	UCoreManager* NewManager = NewObject<UCoreManager>(this, InManagerClass);
	Managers.Add(NewManager);
	NewManager->NativeOnCreate();

	return NewManager;
}

void UManagerSubsystem::UnRegisterManager(TSubclassOf<UCoreManager> InManagerClass)
{
	UCoreManager* RemoveManager = GetManager(InManagerClass, true);
	if (IsValid(RemoveManager))
	{
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
