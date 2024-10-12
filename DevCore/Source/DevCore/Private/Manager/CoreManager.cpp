// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/CoreManager.h"

#include "Manager/GlobalManagerSetting.h"

#define LOCTEXT_NAMESPACE "UCoreManager"

UWorld* UCoreManager::StaticWorld = nullptr;

UCoreManager::UCoreManager(const FObjectInitializer& ObjectInitializer)
{
}

bool UCoreManager::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!UGlobalManagerSetting::Get()->bEnableSubsystem)
	{
		return false;
	}

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

	FWorldDelegates::OnWorldBeginTearDown.AddUObject(this, &UCoreManager::OnWorldEndPlay);
	InWorld.OnWorldMatchStarting.AddUFunction(this, "OnWorldMatchStarting");

	NativeOnActived();
}

void UCoreManager::OnWorldEndPlay(UWorld* InWorld)
{
	FWorldDelegates::OnWorldBeginTearDown.RemoveAll(this);
	NativeOnInactived();
}

void UCoreManager::Deinitialize()
{
	Super::Deinitialize();
	NativeOnDestroy();
}

void UCoreManager::OnWorldMatchStarting_Implementation()
{
	GetWorld()->OnWorldMatchStarting.RemoveAll(this);
}

bool UCoreManager::DoesSupportWorldType(const EWorldType::Type WorldType) const
{
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE || WorldType == EWorldType::GamePreview || WorldType == EWorldType::GameRPC;
}

void UCoreManager::NativeOnCreate()
{
	IProcedureBaseInterface::NativeOnCreate();
	IProcedureBaseInterface::Execute_OnCreate(this);

	StaticWorld = GetWorld();
	LOG(LogManager, Log, TEXT("On Created : %s"), *GetName());
}

void UCoreManager::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();
	IProcedureBaseInterface::Execute_OnRefresh(this);
}

void UCoreManager::NativeOnDestroy()
{
	IProcedureBaseInterface::NativeOnDestroy();

	StaticWorld = nullptr;
	LOG(LogManager, Log, TEXT("On Destroy : %s"), *GetName());
}

void UCoreManager::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();
	IProcedureInterface::Execute_OnActived(this);
	LOG(LogManager, Log, TEXT("On Actived : %s"), *GetName());
}

void UCoreManager::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();
	IProcedureInterface::Execute_OnInactived(this);
	LOG(LogManager, Log, TEXT("On Inactived : %s"), *GetName());
}

bool UCoreManager::IsGameManager() const
{
	const EWorldType::Type WorldType = GetWorld()->WorldType;
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE || WorldType == EWorldType::GamePreview || WorldType == EWorldType::GameRPC;;
}

bool UCoreManager::IsEditorManager() const
{
	const EWorldType::Type WorldType = GetWorld()->WorldType;
	return WorldType == EWorldType::Editor || WorldType == EWorldType::EditorPreview;
}

#undef LOCTEXT_NAMESPACE
