// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/CoreManager.h"

#define LOCTEXT_NAMESPACE "UCoreManager"

UCoreManager::UCoreManager()
{
	ManagerWorld = nullptr;
	DisplayName = LOCTEXT("DisplayName", "Core Manager");
	ProcedureOrder = 0;
}

void UCoreManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	TryUpdateDefaultConfigFile();
}

UWorld* UCoreManager::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject) && ensureMsgf(GetOuter(), TEXT("Manager: %s has a null OuterPrivate in UCoreManager::GetWorld()"), *GetFullName())
		&& !GetOuter()->HasAnyFlags(RF_BeginDestroyed) && !GetOuter()->IsUnreachable())
	{
		return GetOuter()->GetWorld();
	}
	return nullptr;
}

void UCoreManager::NativeOnCreate()
{
	GConfig->Flush(false, *GetSaveIniPath());
	LoadConfig(GetClass(), *GetSaveIniPath());

	IProcedureManagerInterface::NativeOnCreate();
	IProcedureManagerInterface::Execute_OnCreate(this);

	DEBUG(Debug_Manager, Log, TEXT("On Created : %s"), *GetName());
}

void UCoreManager::NativeOnRefresh()
{
	IProcedureManagerInterface::NativeOnRefresh();
	IProcedureManagerInterface::Execute_OnRefresh(this);
}

void UCoreManager::NativeOnDestroy()
{
	TryUpdateDefaultConfigFile();

	IProcedureManagerInterface::NativeOnDestroy();
	IProcedureManagerInterface::Execute_OnDestroy(this);

	DEBUG(Debug_Manager, Log, TEXT("On Destroy : %s"), *GetName());
}

void UCoreManager::NativeOnActived()
{
	IProcedureManagerInterface::NativeOnActived();
	IProcedureManagerInterface::Execute_OnActived(this);

	DEBUG(Debug_Manager, Log, TEXT("On Actived : %s"), *GetName());
}

void UCoreManager::NativeOnInactived()
{
	IProcedureManagerInterface::NativeOnInactived();
	IProcedureManagerInterface::Execute_OnInactived(this);

	DEBUG(Debug_Manager, Log, TEXT("On Inactived : %s"), *GetName());
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
