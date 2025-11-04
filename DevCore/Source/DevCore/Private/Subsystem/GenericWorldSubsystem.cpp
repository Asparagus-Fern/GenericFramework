// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "Subsystem/GenericWorldSubsystem.h"

bool UGenericWorldSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGenericWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FWorldDelegates::OnPreWorldInitialization.AddLambda([this](UWorld* InWorld, const UWorld::InitializationValues IVS)
		{
			FWorldDelegates::OnPreWorldInitialization.RemoveAll(this);
			this->OnPreWorldInitialization(InWorld, IVS);
		}
	);

	FWorldDelegates::OnPostWorldInitialization.AddLambda([this](UWorld* InWorld, const UWorld::InitializationValues IVS)
		{
			FWorldDelegates::OnPostWorldInitialization.RemoveAll(this);
			this->OnPostWorldInitialization(InWorld, IVS);
		}
	);

	FWorldDelegates::OnWorldBeginTearDown.AddLambda([this](UWorld* InWorld)
		{
			InWorld->OnWorldPreBeginPlay.RemoveAll(this);
			InWorld->OnWorldMatchStarting.RemoveAll(this);
			InWorld->OnWorldBeginPlay.RemoveAll(this);
			FWorldDelegates::OnWorldBeginTearDown.RemoveAll(this);
			this->OnWorldBeginTearDown(InWorld);
		}
	);

	FWorldDelegates::OnWorldCleanup.AddLambda([this](UWorld* InWorld, bool bSessionEnded, bool bCleanupResources)
		{
			FWorldDelegates::OnWorldCleanup.RemoveAll(this);
			this->OnWorldCleanup(InWorld, bSessionEnded, bCleanupResources);
		}
	);

	FWorldDelegates::OnPostWorldCleanup.AddLambda([this](UWorld* InWorld, bool bSessionEnded, bool bCleanupResources)
		{
			FWorldDelegates::OnPostWorldCleanup.RemoveAll(this);
			this->OnPostWorldCleanup(InWorld, bSessionEnded, bCleanupResources);
		}
	);
}

void UGenericWorldSubsystem::OnPreWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues IVS)
{
}

void UGenericWorldSubsystem::OnPostWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues IVS)
{
}

void UGenericWorldSubsystem::PostInitialize()
{
	Super::PostInitialize();
}

void UGenericWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);

	InWorld.OnWorldPreBeginPlay.AddLambda([&InWorld, this]()
		{
			InWorld.OnWorldPreBeginPlay.RemoveAll(this);
			OnWorldPreBeginPlay();
		}
	);

	InWorld.OnWorldMatchStarting.AddLambda([&InWorld, this]()
		{
			InWorld.OnWorldMatchStarting.RemoveAll(this);
			OnWorldMatchStarting();
		}
	);

	InWorld.OnWorldBeginPlay.AddLambda([&InWorld, this]()
		{
			InWorld.OnWorldBeginPlay.RemoveAll(this);
			OnWorldPostBeginPlay();
		}
	);
}

void UGenericWorldSubsystem::OnWorldPreBeginPlay()
{
}

void UGenericWorldSubsystem::OnWorldMatchStarting()
{
}

void UGenericWorldSubsystem::OnWorldPostBeginPlay()
{
}

void UGenericWorldSubsystem::OnWorldBeginTearDown(UWorld* InWorld)
{
}

void UGenericWorldSubsystem::OnWorldCleanup(UWorld* InWorld, bool bSessionEnded, bool bCleanupResources)
{
}

void UGenericWorldSubsystem::OnPostWorldCleanup(UWorld* InWorld, bool bSessionEnded, bool bCleanupResources)
{
}

void UGenericWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();

	FWorldDelegates::OnPreWorldInitialization.RemoveAll(this);
	FWorldDelegates::OnPostWorldInitialization.RemoveAll(this);
	FWorldDelegates::OnWorldBeginTearDown.RemoveAll(this);
	FWorldDelegates::OnWorldCleanup.RemoveAll(this);
	FWorldDelegates::OnPostWorldCleanup.RemoveAll(this);
}

bool UGenericWorldSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}
