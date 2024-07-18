// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/CoreManager.h"

#define LOCTEXT_NAMESPACE "UCoreManager"

#if WITH_EDITOR

void UCoreManager::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	TryUpdateDefaultConfigFile();
}

#endif

void UCoreManager::NativeOnCreate()
{
	GConfig->Flush(false, *GConfig->NormalizeConfigIniPath(GetSaveIniPath()));
	LoadConfig(GetClass(), *GetSaveIniPath());

	IProcedureBaseInterface::NativeOnCreate();
	IProcedureBaseInterface::Execute_OnCreate(this);
	DEBUG(Debug_Manager, Log, TEXT("On Created : %s"), *GetName());

	TryUpdateDefaultConfigFile();
}

void UCoreManager::NativeOnRefresh()
{
	IProcedureBaseInterface::NativeOnRefresh();
	IProcedureBaseInterface::Execute_OnRefresh(this);
}

void UCoreManager::NativeOnDestroy()
{
	TryUpdateDefaultConfigFile();

	IProcedureBaseInterface::NativeOnDestroy();
	IProcedureBaseInterface::Execute_OnDestroy(this);
	DEBUG(Debug_Manager, Log, TEXT("On Destroy : %s"), *GetName());
}

void UCoreManager::NativeOnActived()
{
	IProcedureInterface::NativeOnActived();
	IProcedureInterface::Execute_OnActived(this);
	DEBUG(Debug_Manager, Log, TEXT("On Actived : %s"), *GetName());
}

void UCoreManager::NativeOnInactived()
{
	IProcedureInterface::NativeOnInactived();
	IProcedureInterface::Execute_OnInactived(this);
	DEBUG(Debug_Manager, Log, TEXT("On Inactived : %s"), *GetName());
}

void UCoreManager::NativeOnBeginPlay()
{
	IManagerInterface::NativeOnBeginPlay();
	Execute_OnBeginPlay(this);
	DEBUG(Debug_Manager, Log, TEXT("On BeginPlay : %s"), *GetName());
}

void UCoreManager::NativeOnEndPlay()
{
	IManagerInterface::NativeOnEndPlay();
	Execute_OnEndPlay(this);
	DEBUG(Debug_Manager, Log, TEXT("On EndPlay : %s"), *GetName());
}

#undef LOCTEXT_NAMESPACE
