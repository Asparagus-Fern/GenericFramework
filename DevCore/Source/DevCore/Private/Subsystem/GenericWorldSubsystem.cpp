// Copyright ChenTaiye 2025. All Rights Reserved. 

#include "Subsystem/GenericWorldSubsystem.h"

bool UGenericWorldSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UGenericWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FWorldDelegates::OnPreWorldInitialization.AddUObject(this, &UGenericWorldSubsystem::OnPreWorldInitialization);
	FWorldDelegates::OnPostWorldInitialization.AddUObject(this, &UGenericWorldSubsystem::OnPostWorldInitialization);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UGenericWorldSubsystem::PostLoadMapWithWorld);
	FWorldDelegates::OnWorldBeginTearDown.AddUObject(this, &UGenericWorldSubsystem::OnWorldBeginTearDown);
	FWorldDelegates::OnWorldCleanup.AddUObject(this, &UGenericWorldSubsystem::OnWorldCleanup);
	FWorldDelegates::OnPostWorldCleanup.AddUObject(this, &UGenericWorldSubsystem::OnPostWorldCleanup);
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

void UGenericWorldSubsystem::PostLoadMapWithWorld(UWorld* InWorld)
{
}

void UGenericWorldSubsystem::OnWorldBeginTearDown(UWorld* InWorld)
{
	InWorld->OnWorldPreBeginPlay.RemoveAll(this);
	InWorld->OnWorldMatchStarting.RemoveAll(this);
	InWorld->OnWorldBeginPlay.RemoveAll(this);
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
	FCoreUObjectDelegates::PostLoadMapWithWorld.RemoveAll(this);
	FWorldDelegates::OnWorldBeginTearDown.RemoveAll(this);
	FWorldDelegates::OnWorldCleanup.RemoveAll(this);
	FWorldDelegates::OnPostWorldCleanup.RemoveAll(this);
}

bool UGenericWorldSubsystem::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}
