// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/CoreManager.h"

#include "GameplayTagsSettings.h"
#include "Manager/ManagerCollection.h"

#define LOCTEXT_NAMESPACE "UCoreManager"

UCoreManager::UCoreManager()
{
	ManagerWorld = nullptr;
	DisplayName = LOCTEXT("DisplayName", "Core Manager");
	ProcedureOrder;
}

bool UCoreManager::ShouldCreateSubsystem(UObject* Outer) const
{
	return Super::ShouldCreateSubsystem(Outer);
}

void UCoreManager::Initialize(FSubsystemCollectionBase& Collection)
{
	GConfig->Flush(false, *GetSaveIniPath());
	LoadConfig(GetClass(), *GetSaveIniPath());
	DEBUG(Debug_Manager, Log, TEXT("On Created : %s"), *GetName());
	FManagerCollection::Get()->RegisterManager(this);
}

void UCoreManager::Deinitialize()
{
	TryUpdateDefaultConfigFile();
	DEBUG(Debug_Manager, Log, TEXT("On Destroy : %s"), *GetName());
}

void UCoreManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	TryUpdateDefaultConfigFile();
}

UWorld* UCoreManager::GetWorld() const
{
	return ManagerWorld;
}

void UCoreManager::NativeOnCreate()
{
	IProcedureManagerInterface::NativeOnCreate();
	IProcedureManagerInterface::Execute_OnCreate(this);
}

void UCoreManager::NativeOnRefresh()
{
	IProcedureManagerInterface::NativeOnRefresh();
	IProcedureManagerInterface::Execute_OnRefresh(this);
}

void UCoreManager::NativeOnDestroy()
{
	IProcedureManagerInterface::NativeOnDestroy();
	IProcedureManagerInterface::Execute_OnDestroy(this);
}

void UCoreManager::NativeOnActived()
{
	IProcedureManagerInterface::NativeOnActived();
	IProcedureManagerInterface::Execute_OnActived(this);
}

void UCoreManager::NativeOnInactived()
{
	IProcedureManagerInterface::NativeOnInactived();
	IProcedureManagerInterface::Execute_OnInactived(this);
}

void UCoreManager::OnActived_Implementation()
{
	IProcedureManagerInterface::OnActived_Implementation();
}

void UCoreManager::OnInactived_Implementation()
{
	IProcedureManagerInterface::OnInactived_Implementation();
}

void UCoreManager::NativePreProcedureSwitch(EGameplayProcedure InOldProcedure, EGameplayProcedure InNewProcedure)
{
	IProcedureManagerInterface::NativePreProcedureSwitch(InOldProcedure, InNewProcedure);
	IProcedureManagerInterface::Execute_PreProcedureSwitch(this, InOldProcedure, InNewProcedure);
}

void UCoreManager::NativePostProcedureSwitch(EGameplayProcedure InProcedure)
{
	IProcedureManagerInterface::NativePostProcedureSwitch(InProcedure);
	IProcedureManagerInterface::Execute_PostProcedureSwitch(this, InProcedure);
}


#undef LOCTEXT_NAMESPACE
