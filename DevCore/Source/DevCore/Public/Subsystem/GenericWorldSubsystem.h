// Copyright ChenTaiye 2025. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GenericWorldSubsystem.generated.h"

/**
 *
 */
UCLASS()
class DEVCORE_API UGenericWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	virtual void Initialize(FSubsystemCollectionBase& Collection) override; //Subsystem Initialize
	virtual void OnPreWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues IVS); //Delegate Broadcast From FWorldDelegates::OnPreWorldInitialization
	virtual void OnPostWorldInitialization(UWorld* InWorld, const UWorld::InitializationValues IVS); //Delegate Broadcast From FWorldDelegates::OnPostWorldInitialization
	virtual void PostInitialize() override; //Subsystem Post Initialize
	virtual void OnWorldBeginPlay(UWorld& InWorld) override; //Subsystem Begin Play
	virtual void OnWorldPreBeginPlay(); //Before Actor Begin Play
	virtual void OnWorldMatchStarting(); //After Actor Begin Play
	virtual void OnWorldPostBeginPlay(); //Delegate Broadcast From UWorld::OnWorldBeginPlay
	virtual void OnWorldBeginTearDown(UWorld* InWorld); //Before Actor End Play, Delegate Broadcast From FWorldDelegates::OnWorldBeginTearDown
	virtual void OnWorldCleanup(UWorld* InWorld, bool bSessionEnded, bool bCleanupResources); //After Actor End Play, Delegate Broadcast From FWorldDelegates::OnWorldCleanup
	virtual void OnPostWorldCleanup(UWorld* InWorld, bool bSessionEnded, bool bCleanupResources); //Delegate Broadcast From FWorldDelegates::OnPostWorldCleanup
	virtual void Deinitialize() override; //Subsystem Deinitialize
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
};
