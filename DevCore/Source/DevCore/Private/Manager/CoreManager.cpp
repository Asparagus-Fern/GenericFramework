// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/CoreManager.h"

#include "Manager/GlobalManagerSetting.h"

#define LOCTEXT_NAMESPACE "UCoreManager"

UCoreManager::UCoreManager(const FObjectInitializer& ObjectInitializer)
{
}

bool UCoreManager::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!UGlobalManagerSetting::Get()->bEnableManagerSubsystem)
	{
		return false;
	}

	// TArray<UClass*> DerivedClasses;
	// GetDerivedClasses(GetClass(), DerivedClasses);
	//
	// if (!DerivedClasses.IsEmpty())
	// {
	// 	return false;
	// }

	return Super::ShouldCreateSubsystem(Outer);
}

void UCoreManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	NativeOnCreate();
}

void UCoreManager::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	InWorld.OnWorldMatchStarting.AddUFunction(this, "OnWorldMatchStarting");
	NativeOnActived();
}

void UCoreManager::Deinitialize()
{
	Super::Deinitialize();
	NativeOnInactived();
}

void UCoreManager::BeginDestroy()
{
	NativeOnDestroy();
	Super::BeginDestroy();
}

void UCoreManager::OnWorldMatchStarting_Implementation()
{
}

bool UCoreManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UCoreManager::NativeOnCreate()
{
	IProcedureBaseInterface::NativeOnCreate();
	IProcedureBaseInterface::Execute_OnCreate(this);
	LOG(Debug_Manager, Log, TEXT("On Created : %s"), *GetName());
}

void UCoreManager::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();
	IProcedureBaseInterface::Execute_OnRefresh(this);
}

void UCoreManager::NativeOnDestroy()
{
	IProcedureBaseInterface::NativeOnDestroy();
	LOG(Debug_Manager, Log, TEXT("On Destroy : %s"), *GetName());
}

void UCoreManager::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();
	IProcedureInterface::Execute_OnActived(this);
	LOG(Debug_Manager, Log, TEXT("On Actived : %s"), *GetName());
}

void UCoreManager::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();
	IProcedureInterface::Execute_OnInactived(this);
	LOG(Debug_Manager, Log, TEXT("On Inactived : %s"), *GetName());
}

#undef LOCTEXT_NAMESPACE
